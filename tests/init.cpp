#include <sharedptr.cpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("create1", "[CREATE1]")
{
  shared_ptr<int> sp;
  REQUIRE(!sp.get());
}

SCENARIO("create2", "[CREATE2]")
{
  shared_ptr<int> sp(new int(10));
  REQUIRE(*sp==10);
  REQUIRE(sp.use_count()==1);
}

SCENARIO("copy", "[COPY]")
{
  shared_ptr<int> sp1(new int(10));
  shared_ptr<int> sp2=sp1;
  REQUIRE(*sp2==10);
  REQUIRE(sp2.use_count()==2);
}

SCENARIO("assign ", "[ASSIGN]")
{
  shared_ptr<int> sp1(new int(10));
  shared_ptr<int> sp2; 
  sp2=sp1;
  REQUIRE(*sp2==10);
  REQUIRE(sp2.use_count()==2);
}

SCENARIO("use_count", "[COUNT]")
{
   shared_ptr<int> sp1(new int(10));
   shared_ptr<int> sp2=sp1;
   shared_ptr<int> sp3;
   sp3=sp1;
   REQUIRE(sp1.use_count()==3);
}
  
  
