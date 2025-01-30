//******************
//
// scls_foundation_string.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Foundation "Leonhard" part represents the foundation of SCLS.
// It is named after the "Father of modern mathematics", Leonhard Euler.
//
// This file make the use of string simplier.
//
//******************
//
// License (LGPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SCLS_FOUNDATION_STRING
#define SCLS_FOUNDATION_STRING

#include "scls_foundation_binary.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// "std::string" manipulation
	//
	//*********

	// Convert a char array to a string and return it
    std::string char_array_to_string(const char* c_a, unsigned int c_a_size);

	// Returns if a string contains an another string out of 2 (or 1, or 0) different string
	bool contains_string(std::string str, std::string part, std::string out_of_start, std::string out_of_end);
	bool contains_string(std::string str, std::string part, std::string out_of);
    bool contains_string(std::string str, std::string part);

	// Returns the number occurrence of a string in an another string out of 2 (or 1, or 0) different string
    unsigned int count_string(std::string str, std::string part, std::string out_of_start, std::string out_of_end);
    unsigned int count_string(std::string str, std::string part, std::string out_of);
    unsigned int count_string(std::string str, std::string part);

	// Cut a string in a vector where there are the "cut" part out of 2 (or 1, or 0) different string
	std::vector<std::string> cut_string_out_of_2(std::string str, std::string cut, std::string out_of_start, std::string out_of_end, bool erase_blank = false, bool erase_last_if_blank = true);
	std::vector<std::string> cut_string_out_of(std::string str, std::string cut, std::string out_of, bool erase_blank = false, bool erase_last_if_blank = true);
    std::vector<std::string> cut_string(std::string str, std::string cut, bool erase_blank = false, bool erase_last_if_blank = true);

	// Join a vector of string into one string.
    std::string join_string(std::vector<std::string> strings, std::string separation = "");

	// Return the string with only lower case
    std::string lowercase_string(std::string str);

	// Replace a string in an another string.
    std::string replace(std::string str, std::string to_replace, std::string new_str);

	// Returns if a string is a number or not
    bool string_is_number(char to_test);
    bool string_is_number(std::string to_test);
    // Convert a string to a double
    double string_to_double(std::string str);

	//*********
	//
	// "std::string" formatting
	//
	//*********

	// Format a number to a text
	std::string format_number_to_text(double number_to_format, int max_size);
    inline std::string format_number_to_text(double number_to_format){return format_number_to_text(number_to_format, -1);};

    // Format a std::string and its break lines
    std::string format_string_break_line(std::string str, std::string new_break_line);
    std::string format_string(std::string str);
	// Format a std::string and its tabulations
    std::string format_string_tabulations(std::string str, std::string new_tabulation);

	// Format an unformatted text to a plain text
    std::string format_string_as_plain_text(std::string str);
	// Format a plain text to an unformatted text
    std::string format_string_from_plain_text(std::string str);

	// Remove the comment in a text, out of a text
    std::string remove_comment_out_of(std::string str, std::string out_of);
    // Remove spaces from a text
    std::string remove_space(std::string str);

    //*********
	//
	// Text encoding system
	//
	//*********

	// Adds a specific character in UTF-8 with his UTF-8 code
	void add_utf_8(std::string& to_add, unsigned int code);
	// Convert a string in UTF-8 code point to an UTF-8
    std::string to_utf_8(std::string str);

	// Convert a string in UTF-8 to an UTF-8 code point
    bool is_character_utf_8(char chr);
    unsigned char utf_8_level(char character);
    std::string to_utf_8_code_point(std::string str);
	std::string to_utf_8_code_point(const char* character, unsigned int text_size);

    // Returns the offset of size between two position in an utf 8 and code point text
    unsigned int code_point_utf_8_size_offset(std::string utf_8, int analyse_end_utf_8 = -1);
    unsigned int utf_8_code_point_size_offset(std::string utf_8, int analyse_end_code_point = -1);

	//*********
	//
	// XML system
	//
	//*********

	// Balise in a text
    struct Balise_Datas {
        // If the balise
        bool has_content = true;
        // If the balise is a break of line or not
        bool is_break_line = false;
        // If the balise is a paragraph or not
        bool is_paragraph = false;
        // Name of the balise
        std::string name = "";
    };
	// Part of a text gotten by a balising cut
    struct _Text_Balise_Part {
        // Content of the balise containing the part
        std::string balise_content = "";
        // Content of the end of the balise containing the part
        std::string balise_end_content = "";
        // Content of the part
        std::string content = "";
        // Position of the start of the balise (of the first char of the content)
        unsigned int start_position = 0;

        // Returns the total content of the balise
        std::string total_content() const {return balise_content + content + balise_end_content;};
    };
    // XML attribute into a balise
    struct XML_Attribute {
	    // Struct representation a XML attribute
	    // Name of the attribute
	    std::string name = "";
	    // Value of the attribute
	    std::string value = "";
	    // If the value use quotes or not
	    bool value_use_quotes = false;
	};

	// Returns the name of an attribute of a balise
    std::string attribute_name(std::string attribute);
    // Returns the value of an attribute of a balise
    std::string attribute_value(std::string attribute);
	// Return the name of a formatted balise
    std::string balise_name(std::string balise_formatted);

	// Format a balise and return it
    std::string formatted_balise(std::string str);
	// Format a text for being usable with XLM
    std::string format_for_xml(std::string content);

    // Returns if a balise is a closing balise or not
    bool closing_balise(std::string balise);
	// Cut a balise by its attributes
    std::vector<std::string> cut_balise_by_attributes(std::string str);
	// Cut a balise by its attributes out of a certain pattern
    std::vector<std::string> cut_balise_by_attributes_out_of(std::string str, std::string out);
    // Cut a balise by its XML attributes out of a certain pattern
    std::vector<XML_Attribute> cut_balise_by_xml_attributes_out_of(std::string str, std::string out);
	// Cut a string by its balises (including the balises in the vector) out of 2 (or 1, or 0) different string
    std::vector<_Text_Balise_Part> cut_string_by_balise_out_of(std::string str, std::string out, bool erase_blank = false, bool erase_last_if_blank = true);
    std::vector<_Text_Balise_Part> cut_string_by_balise(std::string str, bool erase_blank = false, bool erase_last_if_blank = true);

	class __Balise_Container {
        // Class faciliting the handle of balises
    public:

        // Most simple __Balise_Container constructor
        __Balise_Container() {};
        // __Balise_Container destructor
        ~__Balise_Container() {};

        // Returns the position of the first plain text character in a unformatted text from before a position
        unsigned int first_plain_text_character_before_position_in_informatted_text(const std::string& text_to_convert, int position);
        // Returns a html text in plain text
        std::string plain_text(std::string text_to_convert);
        // Returns a unformatted text position in a plain text
        unsigned int plain_text_position_to_unformatted_text_position(std::string text_to_convert, int position);
        // Return the size of the text
        inline unsigned int plain_text_size(std::string text_to_check) { return plain_text(text_to_check).size(); };

        // Returns the balise of the block or a blank string if it is not
        std::string __block_balise(std::vector<_Text_Balise_Part>& cutted);
        // If the generator contains the style of a balise
        inline bool contains_defined_balise(std::string balise_name) const {return defined_balise(balise_name) != 0;};
        // Cut a block by its sub_blocks and spaces
        std::vector<_Text_Balise_Part> __cut_block(std::string block_text);
        // Cut a multi-block by sub-blocks
        std::vector<std::string> __cut_multi_block(std::string block_text);
        // Return the style of a balise
        inline Balise_Datas* defined_balise(std::string balise_name) const {for(int i = 0;i<static_cast<int>(a_defined_balises.size());i++){if(a_defined_balises.at(i).get()->name==balise_name){return a_defined_balises.at(i).get();}}return 0;};
        inline bool defined_balise_has_content(std::string balise_name) const {Balise_Datas* needed_balise=defined_balise(balise_name);return (needed_balise!=0&&needed_balise->has_content);};
        // Set a balise to the container
        template <typename O = Balise_Datas>
        inline void set_defined_balise(std::shared_ptr<O> balise_datas) {a_defined_balises.push_back(balise_datas);};
        template <typename O = Balise_Datas>
        inline void set_defined_balise(std::string name, std::shared_ptr<O> balise_datas) {balise_datas.get()->name=name;set_defined_balise<O>(balise_datas);};

        // Load the built-ins balises
        virtual void __load_built_in_balises();
        // Load the built-ins balises for the GUI loading
        virtual void __load_built_in_balises_gui();
        // Load the built-ins balises for the window loading
        virtual void __load_built_in_balises_window();

    private:
        // List of each defined balises
        std::vector<std::shared_ptr<Balise_Datas>> a_defined_balises = std::vector<std::shared_ptr<Balise_Datas>>();
    };

    class XML_Text {
	    // Class containing a XML text
    public:

        // Most simple XML_Text constructor, with only a text / open balising
        XML_Text(std::shared_ptr<__Balise_Container> balise_container, std::string text, bool only_text):a_balise_container(balise_container) {a_xml_text = format_for_xml(format_string_break_line(text, "\n"));if(!only_text) {parse_text(text);}};
        XML_Text(std::shared_ptr<__Balise_Container> balise_container, std::string text):XML_Text(balise_container, text, false){};
        XML_Text(std::shared_ptr<__Balise_Container> balise_container, std::string balise_name, std::vector<XML_Attribute> balise_attributes) : a_balise_attributes(balise_attributes),a_balise_container(balise_container),a_balise_name(balise_name) {};
        XML_Text(std::shared_ptr<__Balise_Container> balise_container, std::string balise_name, std::vector<XML_Attribute> balise_attributes, std::string balise_content) : a_balise_attributes(balise_attributes),a_balise_container(balise_container),a_balise_name(balise_name) {parse_text(balise_content);};

        // Parse the text
        void parse_text(std::string new_text);
        // Returns the full text in the XML text
        std::string full_text(bool add_balise) const;
        inline std::string full_text() const {return full_text(true);};

        // Returns an attribute by its name
        inline XML_Attribute xml_attribute(std::string xml_attribute_name) {XML_Attribute to_return;return to_return;};
        // Returns the text in the balise
        inline std::string xml_balise() const {return std::string("<") + xml_balise_name() + std::string(">"); };
        inline std::string xml_balise_end() const {return std::string("</") + xml_balise_name() + std::string(">"); };

        // Getters and setter
        inline __Balise_Container* balise_container() const {return a_balise_container.get();};
        inline bool only_text() const {return a_sub_xml_texts.size() <= 0;};
        inline void set_xml_balise_name(std::string new_xml_balise_name){a_balise_name = new_xml_balise_name;};
        inline std::vector<std::shared_ptr<XML_Text>>& sub_texts() {return a_sub_xml_texts;};
        inline std::string text() const {if(a_sub_xml_texts.size() <= 0){return a_xml_text;}return full_text(false);};
        inline bool use_balise() const {return static_cast<int>(a_balise_name.size()) > 0;};
        inline std::vector<XML_Attribute>& xml_balise_attributes() {return a_balise_attributes;};
        inline std::string xml_balise_name() const {return a_balise_name;};
    private:

        //*********
        //
        // Balise handler
        //
        //*********

        // Attributes of the balise
        std::vector<XML_Attribute> a_balise_attributes = std::vector<XML_Attribute>();
        // Balise container in the text
        std::shared_ptr<__Balise_Container> a_balise_container;
        // Name of the balise
        std::string a_balise_name = "";

        //*********
        //
        // Intern text handler
        //
        //*********

        // Sub-XML text
        std::vector<std::shared_ptr<XML_Text>> a_sub_xml_texts = std::vector<std::shared_ptr<XML_Text>>();
        // XML text
        std::string a_xml_text = "";
	};

	// Create an XML simply from a text
	std::shared_ptr<XML_Text> xml(std::shared_ptr<__Balise_Container> balises, std::string content);

    //*********
	//
	// The String class
	//
	//*********

	class String {
	    // Class representing a SCLS string
    public:// Most simple String constructor
        String() : a_content("") {};
        // Most simple String constructor with "char*"
        String(char* content) : a_content(content) {};
        // Most simple String constructor with "std::string"
        String(std::string content) : a_content(content) {};

        // Returns the String to an std::string in code point / utf-8
        inline std::string to_code_point() const {return to_utf_8_code_point(a_content);};
        inline std::string to_utf_8() const {return a_content;};

        // Return if the String contains an another string
        inline bool contains(std::string part) { return contains_string(a_content, part); };
        // Returns if a string contains an another string out of a string
        inline bool contains(std::string part, std::string out_of) {return contains_string(a_content, part, out_of);};
        // Returns if a string contains an another string out of 2 different string
        inline bool contains(std::string part, std::string out_of_start, std::string out_of_end) {return contains_string(a_content, part, out_of_start, out_of_end);};
        // Returns the number occurrence of a string in an another string
        inline unsigned int count(std::string part) {return count_string(a_content, part);};
        // Returns the number occurrence of a string in an another string out of a string
        inline unsigned int count(std::string part, std::string out_of) {return count_string(a_content, part, out_of);};
        // Returns the number occurrence of a string in an another string out of 2 different string
        inline unsigned int count(std::string part, std::string out_of_start, std::string out_of_end) {return count_string(a_content, part, out_of_start, out_of_end);};
        // Cuts the String by an another string
        inline std::vector<std::string> cut(std::string part_to_cut, bool erase_blank = false, bool erase_last_if_blank = true) { return cut_string(a_content, part_to_cut, erase_blank, erase_last_if_blank); };
        // Cuts the String by an another string out of a string
        inline std::vector<std::string> cut_out_of(std::string part_to_cut, std::string out_of, bool erase_blank = false, bool erase_last_if_blank = true) { return cut_string_out_of(a_content, part_to_cut, out_of, erase_blank, erase_last_if_blank); };
        // Cuts the String by an another string out of 2 different string
        inline std::vector<std::string> cut_out_of_2(std::string part_to_cut, std::string out_of_start, std::string out_of_end, bool erase_blank = false, bool erase_last_if_blank = true) { return cut_string_out_of_2(a_content, part_to_cut, out_of_start, out_of_end, erase_blank, erase_last_if_blank); };
        // Cuts the String by balises (including the balises in the vector)
        inline std::vector<_Text_Balise_Part> cut_by_balise(bool erase_blank = false, bool erase_last_if_blank = true){ return cut_string_by_balise(a_content, erase_blank, erase_last_if_blank); };
        // Formats the string
        inline void format() {a_content = format_string(a_content);};
        // Returns the String formatted
        inline String formatted() {return String(format_string(a_content));};
        // Returns the String formatted for display
        inline String formatted_as_plain_text() {return String(format_string_as_plain_text(a_content));};
        // Returns the String formatted from plain text
        inline String formatted_from_plain_text() {return String(format_string_from_plain_text(a_content));};

        // Returns the position in the content from the position in the String
        inline unsigned int __position_in_content_from_position(int start) const {
            unsigned int to_return = 0;
            for(;to_return<static_cast<unsigned int>(a_content.size())&&static_cast<int>(to_return)<start;to_return++) {
                unsigned char level = utf_8_level(a_content.at(to_return));
                if(level != 0) {start++;to_return+=level;}
            } return to_return;
        };
        inline unsigned int __position_from_position_in_content(int start) const {
            unsigned int to_return = 0;
            for(int i = 0;i<static_cast<int>(a_content.size())&&i<start;i++) {
                unsigned char level = utf_8_level(a_content.at(i));
                i += level;
                to_return++;
            } return to_return;
        };
        // Returns the size of the string
        inline unsigned int size() const {return __position_from_position_in_content(a_content.size());};
        // Substract a string and returns it
        inline String substr(int start, int sub_size) const {
            sub_size = __position_in_content_from_position(start + sub_size);
            start = __position_in_content_from_position(start); sub_size -= start;
            if(sub_size > static_cast<int>(a_content.size()) - start) sub_size = a_content.size() - start;
            return String(a_content.substr(start, sub_size));
        };

        // Returns the String to a char array
        inline const char* to_char_array() const {return a_content.c_str();};
        // Returns the String to a std::string
        inline std::string to_std_string() const {return a_content;};

        // Operator = overload with a char*
        inline String& operator=(const char* other) {a_content = other;return *this;};
        // Operator = overload with a std::string
        inline String& operator=(const std::string& other) {a_content = other;return *this;};
        // Operator = overload with an other String
        inline String& operator=(const String& other) {a_content = other.a_content;return *this;};

        // Operator += overload with char*
        inline String& operator+=(const char* second) { a_content += second; return *this; };
        // Operator += overload with std::string
        inline String& operator+=(const std::string second) { a_content += second; return *this; };
        // Operator += overload with String
        inline String& operator+=(const String second) { a_content += second.a_content; return *this; };

        // Operator == overload with char*
        inline bool operator==(const char* second) const { return a_content.c_str() == second; };
        // Operator == overload with std::string
        inline bool operator==(std::string second) const { return a_content == second; };
        // Operator == overload with String
        inline bool operator==(const String& second) const { return a_content == second.a_content; };

        // Operator + overload with String
        inline String operator+(String second) const {return String(a_content + second.a_content); };

        // Convert to std::string
        operator std::string() const {return to_std_string();};
    private:
        // Content of the string
        std::string a_content = std::string("");
	};

	// Flux output operator of String
    std::ostream& operator<<(std::ostream& strm, const String& str);
}

#endif // SCLS_FOUNDATION_STRING
