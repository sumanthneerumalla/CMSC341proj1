#include "Graph.h"
using namespace std;
#include <iostream>

Graph::Graph(int n) {
  if (n <= 0) {
    throw std::out_of_range("Not possible to insert that number of vertices");
  }

  m_adjLists = new AdjListNode *[n];

  //initialize array to be null, just in case
  for (int i = 0; i < n; ++i) {
    m_adjLists[n] = NULL;
  }

  m_size = n;
}

Graph::Graph(const Graph &G) {
  //copy over member variable for size
  m_size = G.m_size;

  //allocate new dynamic array with that size
  m_adjLists = new AdjListNode *[m_size];

  //iterate through each array and copy over the linked list data.
  AdjListNode *curr2, *next2;

  for (int i = 0; i < m_size; ++i) {
    curr2 = G.m_adjLists[i];

    //iterate through each edge in the second graph, for each vertex
    while (curr2 != NULL) {
      //hold onto the next edge
      next2 = curr2->next;
      //avoid adding the same edge twice.
      if (i < curr2->m_vertex) {
        addEdge(i, curr2->m_vertex);
      }
      curr2 = next2;
    }
  }
}

Graph::~Graph() {
  //iterate through the array of linked list
  AdjListNode *currN, *nextN;
  for (int i = 0; i < m_size; ++i) {
    currN = m_adjLists[i];

    //use a while loop to delete each edge connection
    while (currN != NULL) {
      nextN = currN->next;
      delete currN;
      currN = nextN;
    }

  }

  //delete the array of pointers
  delete[] m_adjLists;
}

void Graph::addEdge(int u, int v) {

  if ((u > m_size - 1) or (v < 0)) {
    throw out_of_range("NbIterator dereference error.");
  }
  if ((v > m_size - 1) or (u < 0)) {
    throw out_of_range("NbIterator dereference error.");
  }

//add an edge to the first vertex
  AdjListNode *next;

  //hold onto the first item in the
  next = m_adjLists[u];
  m_adjLists[u] = new AdjListNode(v, next);

//  cout << "added edge " << u << " to " << v << endl;

  //add the second edge only if the two vertices are not the same
  if (u != v) {
  next = m_adjLists[v];
  m_adjLists[v] = new AdjListNode(u, next);
}
//  cout << "added edge " << v << " to " << u << endl;

};

int Graph::size() {
  return m_size;
}

void Graph::dump() {
  //iterate through the array of linked list
  AdjListNode *curr, *next;

  cout << "Dump out graph (size = " << size() << "):" << endl;
  for (int i = 0; i < size(); ++i) {
    curr = m_adjLists[i];
    cout << "[ " << i << "]: ";
    //use a while loop to print out each edge connection
    while (curr != NULL) {
      next = curr->next;
      cout << curr->m_vertex << " ";
      curr = next;
    }
    cout << endl;

  }
}

const Graph &Graph::operator=(const Graph &rhs) {
  if (this == &rhs) // this is a self assignment checker
  { return *this; }    // returns the pointer to the current object
  // otherwise copy

  //copied code from destructor to deallocate all dynamic memory
  //iterate through the array of linked list
  AdjListNode *curr, *next;
  for (int i = 0; i < m_size; ++i) {
    curr = m_adjLists[0];

    //use a while loop to delete each edge connection
    while (curr != NULL) {
      next = curr->next;
      delete curr;
      curr = next;
    }

  }

  //delete the array of pointers
  delete[] m_adjLists;

  //copied code from copy constructor to copy over new dynamic data

  //copy over member variable for size
  m_size = rhs.m_size;

  //allocate new dynamic array with that size
  m_adjLists = new AdjListNode *[m_size];

  //iterate through each array and copy over the linked list data.
  AdjListNode *curr2, *next2;

  for (int i = 0; i < m_size; ++i) {
    curr2 = rhs.m_adjLists[i];

    //iterate through each edge in the second graph, for each vertex
    while (curr2 != NULL) {
      //hold onto the next edge
      next2 = curr2->next;
      //avoid adding the same edge twice.
      if (i < curr2->m_vertex) {
        addEdge(i, curr2->m_vertex);
      }
      curr2 = next2;
    }
  }
  return *this;
}

Graph::NbIterator Graph::nbBegin(int v) {
  return Graph::NbIterator(this, v, false);
}


Graph::NbIterator Graph::nbEnd(int v) {
  return Graph::NbIterator(this, v, true);
}


Graph::EgIterator Graph::egBegin() {
  return Graph::EgIterator(this, false);
}


Graph::EgIterator Graph::egEnd() {
  return Graph::EgIterator(this, true);
}

Graph::AdjListNode::AdjListNode(int v, Graph::AdjListNode *ptr) {
  m_vertex = v;
  next = ptr;
}

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd) {
  m_Gptr = Gptr;
  m_source = v;
  //honestly i dont see the point of storing these variables if the iterator is just used for
  //comparing the mhwere variable

  //if isend is true we make an end constructor
  if (isEnd == true and Gptr != NULL and v != -1) {
    m_where = NULL;
  }
    //if it is end is not true we make a regular nbiterator, that starts at the beginning of the neighbor list
  else if (isEnd == false and Gptr != NULL and v != -1) {
    m_where = Gptr->m_adjLists[v];
  }
  else {
    m_where = NULL;
    //in any other circumstance, mwhere is not valid
  }

}


bool Graph::NbIterator::operator!=(const Graph::NbIterator &rhs) {
  if (m_where != rhs.m_where) {
    //if the addresses of the mwheres of each iterator are not the same, return true
    return true;
  }
  //otherwise return false
  return false;
}


void Graph::NbIterator::operator++(int dummy) {
  if (m_where != NULL) {
    //increment the pointer only if the next node isn't null
    m_where = m_where->next;
  }
}


int Graph::NbIterator::operator*() {
  if (m_where == NULL) {
    throw out_of_range("NbIterator dereference error.");
  }

  return m_where->m_vertex;
}


Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd) {
  if (Gptr == NULL) { return; }

  m_Gptr = Gptr;

  if (isEnd == true) {
    m_source = Gptr->size() ;
    m_where = NULL;
  }
  else {
    m_source = 0;
    m_where = Gptr->m_adjLists[0];

  }
}

bool Graph::EgIterator::operator!=(const Graph::EgIterator &rhs) {
  if ((m_Gptr == rhs.m_Gptr) and (m_source == rhs.m_source) and (m_where == m_where)) {
    //only if its the same node in the same graph in the same vertex, we return false
    return false;
  }
  //otherwise we return true
  return true;
}


void Graph::EgIterator::operator++(int dummy) {
  do{
//    first increment to the next node
    m_where = m_where->next;
    //keep iterating through to the next msrouce as long as there are null
    while (m_where == NULL) {
      m_source++;
      if (m_source == m_Gptr->m_size) {
        break;
      }
      //pointo the first node in the next source
      m_where = m_Gptr->m_adjLists[m_source];
    }
  }  while((m_where != NULL) and ( m_source > m_where->m_vertex));


    /*bool validNodeNotFound = true;
    while(validNodeNotFound) {

      m_where = m_where;
      m_Gptr = m_Gptr;
      m_Gptr->m_adjLists = m_Gptr->m_adjLists;
      m_source = m_source;

      //iterate through nodes until non NULL node is found
      while (m_where == NULL) {
        m_source++;
        if (m_source > m_Gptr->size() - 1) {
          //if we've gone past the last index
          return;
        }
        m_where = m_Gptr->m_adjLists[m_source];
        cout<< "updated to next source"<<endl;
      }
      //at this point we can guarantee that mwhere is not pointing to a null node
      //iterate one node if m_source < m_where vertex
      if(m_source < m_where->m_vertex){
        //we increment by only one node if this is the case, and recheck for null nodes
        cout<< "incremented to next node"<< endl;
        m_where = m_where->next;
      cout<< m_where<<endl;}
      //hopefully mwhere is pointing to a valid node now
      if((m_where != NULL) and (m_source < m_where->m_vertex)){
        // its not a null node, and the vertex is not less than the msource
        validNodeNotFound = false;
        //loop will not run anymore if this is the case
      }
      if((m_where == NULL) and (m_source == m_Gptr->size()) ){
        //we have reached the end of the graph
  return;    }
      cout<< "source is"<< m_source<<endl;
      }
  */

//  m_where = m_where->next;
//  cout << "mwhere is " << m_where << endl;
//  if (m_where != NULL) {
//    while (m_where->m_vertex < m_source) {
//      if (m_where == NULL) {
//        //if at the end of a linked list, move onto first node in next linked list
//        m_source++;
//        if (m_source > m_Gptr->size() - 1) {
//          return;
//        }
//        m_where = m_Gptr->m_adjLists[m_source];
//      }
//      else {
//        m_where = m_where->next;
//      }
//    }
//  }


//  m_where = m_where->next;
//
//  if(m_where == NULL){
//    m_source = m_source++;
//    m_where = m_Gptr->m_adjLists[m_source];
//  }
//


}

std::pair<int, int> Graph::EgIterator::operator*() {

  if (m_where == NULL) {
    throw out_of_range("EgIterator dereference error.");
  }

  return std::pair<int, int>(m_source, m_where->m_vertex);
}