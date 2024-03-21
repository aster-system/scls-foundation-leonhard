#include "basix.h"

#include <map>

// Test basix_core.h
void test_data_structure() {
    std::string double_1 = "128.48";
    std::string double_2 = "128,48";
    std::string parts = "Leclerc<*>M1A2 Abrams<*><*>Leopard 2A6";
    std::string utf_8 = "éàè";

    basix::print("Test", "Double with .", basix::string_to_double(double_1));
    basix::print("Test", "Double with ,", basix::string_to_double(double_2));

    basix::print("Test", "Contains .", basix::contains(double_1, "."));
    basix::print("Test", "Contains ,", basix::contains(double_1, ","));

    basix::print("Test", "Count 2", basix::count(double_1, "2"));
    basix::print("Test", "Count 5", basix::count(double_1, "5"));
    basix::print("Test", "Count 8", basix::count(double_1, "8"));

    std::vector<std::string> cutted = basix::cut_string(parts, "*");
    for(int i = 0;i<static_cast<int>(cutted.size());i++) {
        basix::print("Test 1", "Part " + std::to_string(i), cutted[i]);
    }

    basix::print("Test", "Joined", basix::join_string(cutted, "-"));

    cutted = basix::cut_string(parts, "<*>");
    for(int i = 0;i<static_cast<int>(cutted.size());i++) {
        basix::print("Test 2", "Part " + std::to_string(i), cutted[i]);
    }

    basix::print("Test", "Joined", basix::join_string(cutted, "/-\\"));

    cutted = basix::cut_string(parts, "<*>", true);
    for(int i = 0;i<static_cast<int>(cutted.size());i++) {
        basix::print("Test 3", "Part " + std::to_string(i), cutted[i]);
    }

    basix::print("Test", "Joined", basix::join_string(cutted));

    // Need more tests
    // basix::print("Test", "Not UTF-8", utf_8);
    // basix::print("Test", "UTF-8", basix::to_utf_8(utf_8));

    unsigned int number_of_test = 10;
    char* test_char_array = new char[number_of_test];
    std::vector<int> test_vector = std::vector<int>();
    for(int i = 0;i<number_of_test;i++) {
        test_char_array[i] = i;
        test_vector.push_back(i);
    }

    basix::swap_char_array(test_char_array, number_of_test);
    test_vector = basix::swap_vector(test_vector);
    for(int i = 0;i<static_cast<int>(test_vector.size());i++) {
        basix::print("Test", "Swapped vector", test_vector[i]);
    }
    for(int i = 0;i<static_cast<int>(test_vector.size());i++) {
        basix::print("Test", "Swapped char array", static_cast<unsigned int>(test_char_array[i]));
    }
    delete[] test_char_array; test_char_array = 0;
}
void test_debugging_helper() {
    double data_1 = 1548.20654;
    std::string data_2 = "Test";

    basix::print("Test", "Tester", data_1);
    basix::print("Test", "Tester", data_2);

    basix::set_can_print(false);

    basix::print("Test", "Tester", "Shouldn't be printed");

    basix::set_can_print(true);
    basix::set_sender_message_separation(basix::to_utf_8(" ==> "));
    basix::set_type_sender_separation(basix::to_utf_8(" ~~~~} "));

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
    test_data_structure();

	return 0;
}
