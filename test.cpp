#include "scls_foundation.h"

#include <map>

// Test scls_foundation_core.h
void test_data_structure() {
    std::string double_1 = "128.48";
    std::string double_2 = "128,48";
    std::string parts = "Leclerc<*>M1A2 Abrams<*><*>Leopard 2A6";
    std::string utf_8 = "éàè";

    scls::print("Test", "Double with .", scls::string_to_double(double_1));
    scls::print("Test", "Double with ,", scls::string_to_double(double_2));

    scls::print("Test", "Contains .", scls::contains(double_1, "."));
    scls::print("Test", "Contains ,", scls::contains(double_1, ","));

    scls::print("Test", "Count 2", scls::count(double_1, "2"));
    scls::print("Test", "Count 5", scls::count(double_1, "5"));
    scls::print("Test", "Count 8", scls::count(double_1, "8"));

    std::vector<std::string> cutted = scls::cut_string(parts, "*");
    for(int i = 0;i<static_cast<int>(cutted.size());i++) {
        scls::print("Test 1", "Part " + std::to_string(i), cutted[i]);
    }

    scls::print("Test", "Joined", scls::join_string(cutted, "-"));

    cutted = scls::cut_string(parts, "<*>");
    for(int i = 0;i<static_cast<int>(cutted.size());i++) {
        scls::print("Test 2", "Part " + std::to_string(i), cutted[i]);
    }

    scls::print("Test", "Joined", scls::join_string(cutted, "/-\\"));

    cutted = scls::cut_string(parts, "<*>", true);
    for(int i = 0;i<static_cast<int>(cutted.size());i++) {
        scls::print("Test 3", "Part " + std::to_string(i), cutted[i]);
    }

    scls::print("Test", "Joined", scls::join_string(cutted));

    scls::Text_Image_Data datas; datas.font = scls::get_system_font("arial");
    scls::Image* img = scls::text_image(scls::to_utf_8(utf_8), datas);
    img->save_png("utf_8.png");
    delete img; img = 0;

    unsigned int number_of_test = 10;
    char* test_char_array = new char[number_of_test];
    std::vector<int> test_vector = std::vector<int>();
    for(int i = 0;i<number_of_test;i++) {
        test_char_array[i] = i;
        test_vector.push_back(i);
    }

    scls::swap_char_array(test_char_array, number_of_test);
    test_vector = scls::swap_vector(test_vector);
    for(int i = 0;i<static_cast<int>(test_vector.size());i++) {
        scls::print("Test", "Swapped vector", test_vector[i]);
    }
    for(int i = 0;i<static_cast<int>(test_vector.size());i++) {
        scls::print("Test", "Swapped char array", static_cast<unsigned int>(test_char_array[i]));
    }
    delete[] test_char_array; test_char_array = 0;
}
void test_debugging_helper() {
    double data_1 = 1548.20654;
    std::string data_2 = "Test";

    scls::print("Test", "Tester", data_1);
    scls::print("Test", "Tester", data_2);

    scls::set_can_print(false);

    scls::print("Test", "Tester", "Shouldn't be printed");

    scls::set_can_print(true);
    scls::set_sender_message_separation(scls::to_utf_8(" ==> "));
    scls::set_type_sender_separation(scls::to_utf_8(" ~~~~} "));

    scls::print("Test", "Tester", "Should be printed");

    scls::set_sender_message_separation(" : ");
    scls::set_type_sender_separation(" -> ");
    scls::authorized_sender().push_back("Tester");
    scls::authorized_type().push_back("Test");

    scls::print("Bug", "Tester", "Shouldn't be printed");
    scls::print("Bug", "Bugger", "Shouldn't be printed");
    scls::print("Test", "Bugger", "Shouldn't be printed");
    scls::print("Test", "Tester", "Should be printed");

    scls::authorized_sender().clear();
    scls::authorized_type().clear();

    scls::print("Bug", "Tester", "Should be printed");
    scls::print("Bug", "Bugger", "Should be printed");
    scls::print("Test", "Bugger", "Should be printed");
    scls::print("Test", "Tester", "Should be printed");
}

int main()
{
    test_data_structure();

	return 0;
}
