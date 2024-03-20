#include "basix.h"

#include <map>

// Test basix_core.h
void test_debugging_helper() {
    double data_1 = 1548.20654;
    std::string data_2 = "Test";

    basix::print("Test", "Tester", data_1);
    basix::print("Test", "Tester", data_2);

    basix::set_can_print(false);

    basix::print("Test", "Tester", "Shouldn't be printed");

    basix::set_can_print(true);
    basix::set_sender_message_separation(basix::to_utf_8(" ==> ", 5));
    basix::set_type_sender_separation(basix::to_utf_8(" ~~~~} ", 7));

    basix::print("Test", "Tester", "Should be printed");

    basix::set_sender_message_separation(" : ");
    basix::set_type_sender_separation(" -> ");
    basix::authorized_sender().push_back("Tester");
    basix::authorized_type().push_back("Test");

    basix::print("Bug", "Tester", "Shouldn't be printed");
    basix::print("Bug", "Bugger", "Shouldn't be printed");
    basix::print("Test", "Bugger", "Shouldn't be printed");
    basix::print("Test", "Tester", "Should be printed");

    basix::authorized_sender().clear();
    basix::authorized_type().clear();

    basix::print("Bug", "Tester", "Should be printed");
    basix::print("Bug", "Bugger", "Should be printed");
    basix::print("Test", "Bugger", "Should be printed");
    basix::print("Test", "Tester", "Should be printed");
}

int main()
{
    test_debugging_helper();

	return 0;
}
