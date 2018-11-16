#include "data.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>


const double distance_scale = 1.0 / distance_precision;

const std::vector<std::string> problem_type_name = {"TSP", "NO_PROBLEM_TYPE"};
const std::vector<std::string> edge_weight_type_name = {"EXPLICIT", "EUC_2D", "EUC_3D", "GEO", "NO_WEIGHT_TYPE"};
const std::vector<std::string> edge_weight_format_name = {"FUNCTION", "LOWER_DIAG_ROW", "NO_WEIGHT_FORMAT"};
const std::vector<std::string> edge_data_format_name = {"EDGE_LIST", "NO_DATA_FORMAT"};
const std::vector<std::string> node_coord_type_name = {"TWOD_COORDS", "THREED_COORDS", "NO_COORDS", "NO_COORD_TYPE"};
const std::vector<std::string> display_data_type_name = {"NO_DISPLAY", "NO_DATA_TYPE"};


TSPLIB_Info::TSPLIB_Info ()
{
  clear();
}

void TSPLIB_Info::clear()
{
  problem_type = NO_PROBLEM_TYPE;
  edge_weight_type = NO_WEIGHT_TYPE;
  edge_weight_format = NO_WEIGHT_FORMAT;
  edge_data_format = NO_DATA_FORMAT;
  node_coord_type = NO_COORD_TYPE;
  display_data_type = NO_DATA_TYPE;
}


std::ostream & operator<< (std::ostream & os, const TSPLIB_Info & info)
{
  os << "current info:\n"
     << "  problem type:       " << problem_type_name[info.problem_type] << "\n"
     << "  edge weight type:   " << edge_weight_type_name[info.edge_weight_type] << "\n"
     << "  edge weight format: " << edge_weight_format_name[info.edge_weight_format] << "\n"
     << "  edge data format:   " << edge_data_format_name[info.edge_data_format] << "\n"
     << "  node coord type:    " << node_coord_type_name[info.node_coord_type] << "\n"
     << "  display data type:  " << display_data_type_name[info.display_data_type];
  return os;
}


Data::Data (RNG & rng): rng_(rng)
{
}


Data::Data (const std::string & filename, RNG & rng): rng_(rng)
{
  readTSPLIBFormat (filename);
}


void Data::clear ()
{
  name_.clear();
  info_.clear();
  nodes_.clear();
  distance_.clear();
}


int readEntry (std::ifstream & is, std::string & keyword, std::string & value)
{
  std::string str;

  std::getline(is, str);
  std::istringstream iss(str);
  if (iss >> keyword)
  {
    std::transform(keyword.begin(), keyword.end(), keyword.begin(), toupper);
    if (iss >> value)
    {
      std::transform(value.begin(), value.end(), value.begin(), toupper);
      return 2;
    }
    return 1;
  }
  return 0;
}


int readSection (std::ifstream & is, std::string & section)
{
  std::string str;

  std::getline(is, str);
  std::istringstream iss(str);
  if (iss >> section)
    return 1;
  return 0;
}


void Data::readSpecification (std::ifstream & is, std::string & keyword)
{
  std::string value;

  // initialize the TSPLIB infos and the instance
  info_.clear();
  nodes_.clear();

  // scan the problem specifications
  bool stop = false;
  do
  {
    // read a new specification line
    int res = readEntry(is, keyword, value);
    if (res == 0)
    {
      std::cerr << "error: wrong line format" << std::endl;
      exit(1);
    }
    else if (res == 1)
    {
      //std::cout << "reading the data specification done" << std::endl;
      stop = true;
    }
    else
    {
      if (keyword == "NAME:")
      {
        // specify the instance name
        name_ = value;
      }
      else if (keyword == "TYPE:")
      {
        // specify the problem type
        if (value == "TSP")
          info_.problem_type = TSP;
        else
        {
          std::cerr << "error: unsupported problem type (" << value << ")" << std::endl;
          exit(1);
        }
      }
      else if (keyword == "COMMENT:")
      {
        // nothing to do
      }
      else if (keyword == "DIMENSION:")
      {
        // specify the instance size
        std::istringstream iss(value);
        unsigned n;
        if (!(iss >> n))
        {
          std::cerr << "error: wrong size type (got \"" << value << "\", integer expected)" << std::endl;
          exit(1);
        }
        assert((n) && "error: positive size expected");

        // memory allocation
        nodes_.resize(n);
        for (auto & e: nodes_)
        {
          e.neighbours_.resize(n);
        }
        distance_.resize(n);
        for (auto & e: distance_)
        {
          e.resize(n);
        }
      }
      else if (keyword == "CAPACITY:")
      {
        // specify the vehicles capacity
        std::cerr << "warning: unsupported capacity (\"" << value << "\")" << std::endl;
      }
      else if (keyword == "EDGE_WEIGHT_TYPE:")
      {
        // specify the way to compute distances
        for (unsigned i = 0; (i < NO_WEIGHT_TYPE) && (info_.edge_weight_type == NO_WEIGHT_TYPE); ++i)
        {
          if (value == edge_weight_type_name[i])
            info_.edge_weight_type = static_cast<Edge_weight_type>(i);
        }
        if (info_.edge_weight_type == NO_WEIGHT_TYPE)
        {
          std::cerr << "error: unsupported edge weight type (\"" << value << "\")" << std::endl;
          exit(1);
        }
        if ((info_.edge_weight_type == GEO) || (info_.edge_weight_type == EUC_2D))
          info_.node_coord_type = TWOD_COORDS;
        else if (info_.edge_weight_type == EUC_3D)
          info_.node_coord_type = THREED_COORDS;
      }
      else if (keyword == "EDGE_WEIGHT_FORMAT:")
      {
        // specify the way distances are stored if they are explicit
        for (unsigned i = 0; (i < NO_WEIGHT_FORMAT) && (info_.edge_weight_format == NO_WEIGHT_FORMAT); ++i)
        {
          if (value == edge_weight_format_name[i])
            info_.edge_weight_format = static_cast<Edge_weight_format>(i);
        }
        if (info_.edge_weight_format == NO_WEIGHT_FORMAT)
        {
          std::cerr << "error: unsupported edge weight format (\"" << value << "\")" << std::endl;
          exit(1);
        }
        if ((info_.edge_weight_format == FUNCTION) && ((info_.edge_weight_type == EXPLICIT) || (info_.edge_weight_type == NO_WEIGHT_TYPE)))
        {
          std::cerr << "error: edge weight format (\"" << value << "\") incomptible with type "
                    << edge_weight_type_name[info_.edge_weight_type] << std::endl;
          exit(1);
        }
      }
      else if (keyword == "EDGE_DATA_FORMAT:")
      {
        std::cerr << "warning: unhandled edge data format (\"" << value << "\")" << std::endl;
      }
      else if (keyword == "NODE_COORD_TYPE:")
      {
        // specify the way distances are stored if they are explicit
        for (unsigned i = 0; (i < NO_COORD_TYPE) && (info_.node_coord_type == NO_COORD_TYPE); ++i)
        {
          if (value == node_coord_type_name[i])
            info_.node_coord_type = static_cast<Node_coord_type>(i);
        }
        if (info_.node_coord_type == NO_COORD_TYPE)
        {
          std::cerr << "error: unsupported node coord type (\"" << value << "\")" << std::endl;
          exit(1);
        }
      }
      else if (keyword == "DISPLAY_DATA_TYPE:")
      {
        std::cerr << "warning: unhandled node coord type (\"" << value << "\")" << std::endl;
      }
      else
      {
        std::cerr << "error: wrong arguments (\"" << keyword << "\" \"" << value << "\")" << std::endl;
        exit(1);
     }
    }
  } while (stop == false);
}


void Data::buildNeighborhoodLists ()
{
  unsigned cpt = 0;
  for (Node & n: nodes_)
  {
    assert((n.id() == cpt) && "error: wrong node id");
    unsigned old_self = distance_[cpt][cpt];
    distance_[cpt][cpt] = Data::INFINITE;
    n.compute_neighbours(distance_[cpt]);
    distance_[cpt][cpt] = old_self;
    ++cpt;
  }
}


typedef int (* Distance_function) (const Node &, const Node &); // distance function pointer

const auto NINT = lround; // C++11 function alias, sort of...
//inline int NINT (double x) { return int((x >= 0.0) ? x + 0.5: x - 0.5); }
//#define NINT(x) int((x) + 0.5)

int euc2DDistance (const Node & node1, const Node & node2)
{
  /* L2-norm */
  const double deltaX = node1.x() - node2.x();
  const double deltaY = node1.y() - node2.y();
  return (NINT(distance_scale * sqrt(deltaX * deltaX + deltaY * deltaY)));
}

int euc3DDistance (const Node & node1, const Node & node2)
{
  /* L2-norm */
  const double deltaX = node1.x() - node2.x();
  const double deltaY = node1.y() - node2.y();
  const double deltaZ = node1.z() - node2.z();
  return (NINT(distance_scale * sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ)));
}

int geoDistance (const Node & node1, const Node & node2)
{
  // get the latitude / longitude for the first node
  double degree1 = int(node1.x()); // NOTE use NINT ?
  double minute1 = node1.x() - degree1;
  double latitude1 = M_PI * (degree1 + 5.0 * minute1 / 3.0) / 180.0;
  degree1 = int(node1.y()); // NOTE use NINT ?
  minute1 = node1.y() - degree1;
  double longitude1 = M_PI * (degree1 + 5.0 * minute1 / 3.0) / 180.0;

  /* get the latitude / longitude for the second node */
  double degree2 = int(node2.x()); // NOTE use NINT ?
  double minute2 = node2.x() - degree2;
  double latitude2 = M_PI * (degree2 + 5.0 * minute2 / 3.0) / 180.0;
  degree2 = int(node2.y()); // NOTE use NINT ?
  minute2 = node2.y() - degree2;
  double longitude2 = M_PI * (degree2 + 5.0 * minute2 / 3.0) / 180.0;

  /* compute the geometrical distance in kilometers */
  #define EARTH_RADIUS 6378.388
  double q1 = cos(longitude1 - longitude2);
  double q2 = cos(latitude1 - latitude2);
  double q3 = cos(latitude1 + latitude2);
  return (int(distance_scale * EARTH_RADIUS * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0));
}


void Data::buildDistanceMatrix ()
{
  Distance_function distance;

  // set the right distance function
  switch (info_.edge_weight_type)
  {
    case EUC_2D: distance = &euc2DDistance; break;
    case EUC_3D: distance = &euc3DDistance; break;
    case GEO: distance = &geoDistance; break;
    default: std::cerr << "error: unsupported distance function" << std::endl; exit(1);
  }

  /* for each pair of nodes */
  const unsigned n = nodes_.size();
  for (unsigned i = 0; i < n; ++i)
  {
    for (unsigned j = 0; j < i; ++j)
    {
      if (j != i)
      {
        int dist = distance(nodes_[i], nodes_[j]);
        assert((dist >= 0) && "error: negative distance");
        distance_[i][j] = distance_[j][i] = unsigned(dist);
      }
      distance_[i][i] = 0; // was set to Data::INFINITE;
    }
  }
}


void Data::readNodeCoords (std::ifstream & is)
{
  unsigned id, cpt;
  double x, y, z;

  cpt = 0;
  switch (info_.node_coord_type)
  {
    case TWOD_COORDS: // 2D coordinates
      for (Node & node: nodes_)
      {
        is >> id >> x >> y;
        node.id_ = cpt;
        node.public_id_ = id;
        node.x_ = x;
        node.y_ = y;
        node.z_ = Data::INFINITE;

        ++cpt;
      }
      break;
    case THREED_COORDS: // 3D coordinates
      for (Node & node:nodes_)
      {
        is >> id >> x >> y >> z;
        node.id_ = cpt;
        node.public_id_ = id;
        node.x_ = x;
        node.y_ = y;
        node.z_ = z;

        ++cpt;
      }
      break;
    default:
      std::cerr << "error: unhandled format (\"" << edge_weight_format_name[info_.edge_weight_format] << "\")"
                << std::endl;
      exit(1);
  }

  buildDistanceMatrix ();
  buildNeighborhoodLists ();
}


void Data::readEdgeWeights (std::ifstream & is)
{
  double dist;

  if (info_.edge_weight_format == LOWER_DIAG_ROW)
  {
    // row-wise lower diagonal storage
      const unsigned n = nodes_.size();
      for (unsigned i = 0; i < n; ++i)
      {
        for (unsigned j = 0; j < i; ++j)
        {
          is >> dist;
          assert((dist >= 0) && "error: negative distance");
          distance_[i][j] = distance_[j][i] = unsigned(dist);
        }
        is >> dist;
        assert((dist >= 0) && "error: negative distance");
        distance_[i][i] = unsigned(dist);
      }
  }
  else
  {
      std::cerr << "error: unhandled format (\"" << edge_weight_format_name[info_.edge_weight_format] << "\")"
                << std::endl;
      exit(1);
  }

  buildNeighborhoodLists();
}


void Data::readData (std::ifstream & is, const std::string & format)
{
  // scan the problem data format
  if (format == "EOF")
  {
    std::cout << "reading the data section done" << std::endl;
  }
  else if (format == "NODE_COORD_SECTION")
  {
    readNodeCoords (is);
  }
  else if (format == "EDGE_WEIGHT_SECTION")
  {
    readEdgeWeights (is);
  }
  else
  {
    std::cerr << "warning: unhandled format (\"" << format << "\")" << std::endl;
  }
}


void Data::readTSPLIBFormat (const std::string & filename)
{
  // open the instance
  std::ifstream is(filename);
  if (!is.is_open())
  {
    std::cerr << "error: unable to open instance file \"" << filename << "\"" << std::endl;
    exit(1);
  }

  // clean the data
  clear();

  // read the specification section
  std::string format;
  readSpecification (is, format);
  //std::cout << "TSPLIB specifications: " << info_ << std::endl;

  // read the data section
  readData (is, format);

  // close the instance file
  is.close();

  // load the corresponding best known value
  bkr_.load(filename);
}


void Data::check () const
{
  const unsigned n = nodes_.size();

  // check the distance matrix
  assert((distance_.size() == n) && "error: wrong matrix dimension");
  for (size_t i = 0; i < n; ++i)
  {
    // vector size
    assert((distance_[i].size() == n) && "error: wrong matrix dimension");

    // values (check symmetry)
    for (size_t j = 0; j < i; ++j)
    {
      if (i == j)
        continue;

      assert((distance_[i][j] == distance_[i][j]) && "error: wrong distance value"); // TODO
      assert((distance_[i][j] == distance_[j][i]) && "error: distance matrix not symmetric");
    }

    // distance to self
    if (distance_[i][i] != 0)
      std::cerr << "error: distance_[" << i << "][" << i << "] = " << distance_[i][i] << std::endl;
    assert((distance_[i][i] == 0) && "error: wrong self_distance");
  }

  // check each node
  unsigned cpt = 0;
  for (const Node & n: nodes_)
  {
    assert((n.id() == cpt) && "error: wrong node id");
    n.check(distance_[cpt]);
    ++cpt;
  }
}


std::ostream & operator<< (std::ostream & os, const Data & d)
{
  // display global data
  os << "\n\nProblem " << d.name() << ": " << d.size() << " nodes, BKR = " << d.bkr().value_ << "\n";

  if ((false))
  {
    // display the nodes
    const unsigned n = d.size();
    for (const Node & node: d.nodes())
    {
      os << " n " << node.id() << ": " << node;

      // display the neighbourhood
      os << " neigh=(";
      std::copy(node.neighbours().begin(), node.neighbours().end(), std::ostream_iterator<unsigned>(os, " "));
      os << ")\n";
    }

    // display the distance matrix
    os << "distance matrix:\n";
    for (unsigned i = 0; i < n; ++i)
    {
      for (unsigned j = 0; j < n; ++j)
        os << " " << d(i,j);
      os << "\n";
    }
  }

  return os;
}
