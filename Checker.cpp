#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Struct to represent limit boundaries
struct ParameterLimit {
  float lower;
  float upper;
  string name;
};

// Enum to indicate type of breach
enum BreachType { NORMAL, TOO_LOW, TOO_HIGH };

// Function to check whether value is within limits
BreachType checkLimit(float value, const ParameterLimit& limit) {
  if (value < limit.lower) {
    return TOO_LOW;
  }
  if (value > limit.upper) {
    return TOO_HIGH;
  }
  return NORMAL;
}

// Print breach message (kept outside pure function)
void reportBreach(const string& paramName, BreachType breach) {
  if (breach == TOO_LOW) {
    cout << paramName << " is too low!\n";
  } else if (breach == TOO_HIGH) {
    cout << paramName << " is too high!\n";
  }
}

// Master checker that uses all parameters
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool isBatteryOk = true;

  ParameterLimit tempLimit = {0, 45, "Temperature"};
  ParameterLimit socLimit = {20, 80, "State of Charge"};
  ParameterLimit chargeRateLimit = {0, 0.8, "Charge Rate"};

  BreachType tempStatus = checkLimit(temperature, tempLimit);
  BreachType socStatus = checkLimit(soc, socLimit);
  BreachType chargeRateStatus = checkLimit(chargeRate, chargeRateLimit);

  if (tempStatus != NORMAL) {
    reportBreach(tempLimit.name, tempStatus);
    isBatteryOk = false;
  }

  if (socStatus != NORMAL) {
    reportBreach(socLimit.name, socStatus);
    isBatteryOk = false;
  }

  if (chargeRateStatus != NORMAL) {
    reportBreach(chargeRateLimit.name, chargeRateStatus);
    isBatteryOk = false;
  }

  return isBatteryOk;
}

// ------------ TEST CASES ------------

void runTests() {
  assert(batteryIsOk(25, 70, 0.7) == true);     // All OK
  assert(batteryIsOk(-1, 70, 0.7) == false);    // Temp low
  assert(batteryIsOk(46, 70, 0.7) == false);    // Temp high
  assert(batteryIsOk(25, 19, 0.7) == false);    // SOC low
  assert(batteryIsOk(25, 81, 0.7) == false);    // SOC high
  assert(batteryIsOk(25, 70, 0.9) == false);    // Charge rate high
  assert(batteryIsOk(50, 85, 0) == false);      // Temp & SOC high
  assert(batteryIsOk(-5, 15, 0.9) == false);    // All bad
}

int main() {
  runTests();
  cout << "All tests passed.\n";
}
