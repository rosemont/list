/* driver for xlist
 *
 */

#include <iostream>
#include "xlist.h"

using namespace std;

int main() {
  xlist mylist;

  for (int i=0; i<10; i++) mylist.pushfront(i);
  mylist.showme();

  xlist newlist(mylist);
  newlist.showme();
}


