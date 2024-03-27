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

    #ifdef SCLS_FOUNDATION_IMAGE
    scls::Text_Image_Data datas; datas.font = scls::get_system_font("arial");
    scls::Image* img = scls::text_image(scls::to_utf_8(utf_8), datas);
    img->save_png("utf_8.png");
    delete img; img = 0;
    #endif // SCLS_FOUNDATION_IMAGE

    unsigned int number_of_test = 10;
    char* test_char_array = new char[number_of_test];
    std::vector<int> test_vector = std::vector<int>();
    for(int i = 0;i<static_cast<int>(number_of_test);i++) {
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

// Test scls_foundation_binary.h
void test_binary_object() {
    scls::Bytes_Set binary_number = scls::Bytes_Set();

    int to_add_size = 250;
    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_int64(static_cast<int64_t>(i), true);
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_double(static_cast<double>(i) / 1024.0, true);
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_uint(static_cast<unsigned int>(i), true);
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_int(static_cast<int>(-128 + i), true);
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_ushort(static_cast<unsigned short>(i), true);
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_short(static_cast<short>(-128 + i), true);
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_data(static_cast<unsigned char>(i));
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_data(static_cast<char>(-128 + i));
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_data(static_cast<unsigned char>(i));
    }

    for(int i = 0;i<to_add_size;i++) {
        binary_number.add_data(static_cast<char>(-128 + i));
    }

    scls::print("Test", "Bytes_Set good", binary_number[15]);
    scls::print("Test", "Bytes_Set not good", binary_number[1500000000]);

    binary_number.save("binary_number.binary");

    scls::Bytes_Set binary_text = scls::Bytes_Set();
    std::string to_write = scls::to_utf_8("Le char Leclerc est un char de combat français de 4ème génération, conçu dans les années 90.");
    binary_text.add_string(to_write);

    binary_text.save("binary_text.binary");

    scls::Bytes_Set _binary_read = scls::Bytes_Set();
    _binary_read.load_from_file("binary_text.binary");
    scls::Bytes_Set binary_read = scls::Bytes_Set(_binary_read);

    std::string all = binary_read.extract_string(to_write.size());
    scls::print("Debug", "Base", to_write);
    scls::print("Debug", "Text", all);

    binary_read.load_from_file("binary_number.binary");
    unsigned int current_size = 0;
    scls::print("Debug", "Int64 (50)", binary_read.extract_int64(current_size + 50 * 8, true));
    current_size += 250 * 8;
    scls::print("Debug", "Double (50 / 1024 = 0.0488281)", binary_read.extract_double(current_size + 50 * 8, true));
    current_size += 250 * 8;
    scls::print("Debug", "UInt (50)", binary_read.extract_uint(current_size + 50 * 4, true));
    scls::print("Debug", "Int (-128 + 50 = -78)", binary_read.extract_int(current_size + 300 * 4, true));
    current_size += 500 * 4;
    scls::print("Debug", "UShort (50)", binary_read.extract_ushort(current_size + 50 * 2, true));
    scls::print("Debug", "Short (-128 + 50 = -78)", binary_read.extract_short(current_size + 300 * 2, true));
    current_size += 500 * 2;
    scls::print("Debug", "Char (50)", static_cast<int>(binary_read.extract_data(current_size + 50)));
}

// Test scls_foundation_file.h
void test_file() {
    std::string path_1 = "C://Programs/Aster System/data.txt";
    std::string path_2 = "C://Programs/Aster System/datas";

    scls::print("Test", "SCLS Path 1 extension", scls::file_extension(path_1));
    scls::print("Test", "SCLS Path 1 name", scls::file_name(path_1));

    scls::print("Test", "SCLS Path 2 extension", scls::file_extension(path_2));
    scls::print("Test", "SCLS Path 2 name", scls::file_name(path_2));

    std::string path_5 = "scls_foundation_directory/scls_foundation_file.h";
    std::string path_6 = "C:\\Users\\Public\\Desktop";

    std::vector<std::string> content = scls::directory_content(path_5);
    for(int i = 0;i<static_cast<int>(content.size());i++) {
        scls::print("Test", "SCLS Path 5 file " + std::to_string(i), content[i]);
    }

    content = scls::directory_content(path_6, true);
    for(int i = 0;i<static_cast<int>(content.size());i++) {
        scls::print("Test", "SCLS Path 6 file " + std::to_string(i), content[i]);
    }

    scls::write_in_file("test.txt", scls::to_utf_8("Le char Leclerc à Paris"));
    scls::print("Test", "SCLS File", scls::read_file("test.txt"));
}

// Test scls_foundation_math.h
void test_math() {
    scls::print("Test", "SCLS Math", scls::normalize_value(145, 0, 256));
    scls::print("Test", "SCLS Math", scls::normalize_value(256 + 145, 0, 256));
    scls::print("Test", "SCLS Math", scls::normalize_value(256 * 1547 + 145, 0, 256));
    scls::print("Test", "SCLS Math", scls::normalize_value(-111, 0, 256));

    scls::print("Test", "SCLS Math", scls::normalize_value(-111, 256, 0));
    scls::print("Test", "SCLS Math", scls::normalize_value(-111, 256, 256));

    scls::print("Test", "SCLS Math", scls::normalize_value(-129, -128, 128));
    scls::print("Test", "SCLS Math", scls::normalize_value(128, -128, 128));

    scls::print("Test", "SCLS Math", scls::sign(1546754));
    scls::print("Test", "SCLS Math", scls::sign(-7647597));
}

int main()
{
    scls::print("Test", "SCLS", scls::to_utf_8("Début du test de SCLS Foundation Leonhard :\n"));
    scls::print("Test", "SCLS", scls::to_utf_8("Test des structure des données."));
    test_data_structure();
    scls::print("Test", "SCLS", scls::to_utf_8("Test terminé.\nTest du système de debug."));
    test_debugging_helper();
    scls::print("Test", "SCLS", scls::to_utf_8("Test terminé.\n\nTest du système binaire."));
    test_binary_object();
    scls::print("Test", "SCLS", scls::to_utf_8("Test terminé.\n\nTest du système de fichier."));
    test_file();
    scls::print("Test", "SCLS", scls::to_utf_8("Test terminé.\n\nTest du système mathématique."));
    test_math();
    scls::print("Test", "SCLS", scls::to_utf_8("Test terminé.\n\nTout les tests ont été réalisé."));

    std::string a = "";
    std::cin >> a;

    return 0;
}
