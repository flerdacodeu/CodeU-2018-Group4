#ifndef TESTREARRANGECARS_H
#define TESTREARRANGECARS_H

#include "RearrangeCars.h"
#include "codeu_test_lib.h"

class TestRearrangeCars {
public:
	void runAllTests();
private:
	void testValidRearrangingOfCars();
	void testValidRearrangingOfCarsWithConstrains();
	void testValidRearrangingOfCarsWithConstrainsWhenDisplacedCarsCanNotBeMovedToFreeSpace1();
	void testValidRearrangingOfCarsWithConstrainsWhenDisplacedCarsCanNotBeMovedToFreeSpace2();
};

#endif
