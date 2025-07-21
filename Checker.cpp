#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct ParameterLimit {
  float lower;
  float upper;
  string name;
};

enum BreachType { NORMAL, TOO_LOW, TOO_HIGH };

BreachType checkLimit(float value, const ParameterLimit& limit) {
  if (value < limit.lower) return TOO_LOW;
  if (value > limit.upper) return TOO_HIGH;
  return NORMAL;
}

bool checkAndReport(float value, const ParameterLimit& limit) {
  BreachType breach = checkLimit(value, limit);
  if (breach == TOO_LOW) {
    cout << limit.name << " is too low!\n";
    return false;
  }
  if (breach == TOO_HIGH) {
    cout << limit.name << " is too high!\n";
    return false;
  }
  return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  ParameterLimit tempLimit = {0, 45, "Temperature"};
  ParameterLimit socLimit = {20, 80, "State of Charge"};
  ParameterLimit chargeLimit = {0, 0.8, "Charge Rate"};

  bool tempOk = checkAndReport(temperature, tempLimit);
  bool socOk = checkAndReport(soc, socLimit);
  bool chargeOk = checkAndReport(chargeRate, chargeLimit);

  return tempOk && socOk && chargeOk;
}

// ------------ TEST CASES ------------

void runTests() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(-1, 70, 0.7) == false);
  assert(batteryIsOk(25, 85, 0.7) == false);
  assert(batteryIsOk(25, 70, 0.9) == false);
  assert(batteryIsOk(46, 19, 0.9) == false);
}

int main() {
  runTests();
  cout << "All tests passed.\n";
}
