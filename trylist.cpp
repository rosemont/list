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
  
  xlist::const_iterator itor;
  for (itor=mylist.begin(); itor!=mylist.end(); ++itor)
    cout << *itor << " . ";
  cout << endl;
}


