#include <iostream>
#include "protobuf/config.pb.h"

using namespace std;
using namespace test;

void proto_read(void)
{

}
void proto_write(void)
{
	first pro_ins;
	pro_ins.set_a(10);
	cout<<pro_ins.a()<<endl;
	cout<<pro_ins.d_size()<<endl;
	pro_ins.add_d(2);
	pro_ins.add_d(2);
	pro_ins.add_d(2);
	pro_ins.add_d(2);
	pro_ins.set_d(3, 100);
	cout<<pro_ins.d_size()<<endl;
	cout<<pro_ins.d(3)<<endl;

}
int main(void)
{
	// test write operation
	proto_write();

	// test read operation
	proto_read();
	return 0;
}
