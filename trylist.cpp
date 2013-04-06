/* driver for xlist
 *
 */

#include <iostream>
#include "xlist.h"

using namespace std;

int main() {
  xlist mylist;
  for (int i=0; i<10; i++) mylist.push_front(i);
  xlist newlist(mylist);
  xlist n2list(newlist.begin(),newlist.end());
  
  xlist::const_iterator itor;
  cout << "size of the list is: " << n2list.size() << endl;
  for (itor=n2list.begin(); itor!=n2list.end(); ++itor)
    cout << *itor << " . ";
  cout << endl;
}


