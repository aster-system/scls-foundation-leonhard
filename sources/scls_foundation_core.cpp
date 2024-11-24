//******************
//
// scls_foundation_core.h
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
// This file contains the core of the library.
//

// Include the good header file
#include "../scls_foundation_directory/scls_foundation_binary.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Debugging helper
	//
	//*********

	// Each variables are initialised with SCLS_FOUNDATION_CORE_INIT
	// Static vector of each authorized sender to be printed
    std::vector<std::string> __authorized_sender = std::vector<std::string>();;
	// Static vector of each authorized type to be printed
    std::vector<std::string> __authorized_type = std::vector<std::string>();;
	// Static bool, usefull in debugging to tell to SCLS if the "print" function is enable or not
    bool __can_print = true;
	// Static string, separation between the sender and the message in the "print" function
    std::string __sender_message_separation = std::string(" : ");
	// Static string, separation between the type and the sender in the "print" function
    std::string __type_sender_separation = std::string(" -> ");

	// Return a reference to "__authorized_sender"
    std::vector<std::string>& authorized_sender() {return __authorized_sender;};
	// Return a reference to "__authorized_type"
    std::vector<std::string>& authorized_type() {return __authorized_type;};
	// Return the value of "__can_print".
    bool can_print() { return __can_print; };
	// Returns if a sender is authorized or not
    bool is_sender_authorized(std::string sender_to_test) {
        if(authorized_sender().size() == 0) return true;

        for(int i = 0;i<static_cast<int>(authorized_sender().size());i++) {
            if(authorized_sender()[i] == sender_to_test) return true;
        }
        return false;
	}
	// Returns if a type is authorized or not
    bool is_type_authorized(std::string type_to_test) {
        if(authorized_type().size() == 0) return true;

        for(int i = 0;i<static_cast<int>(authorized_type().size());i++) {
            if(authorized_type()[i] == type_to_test) return true;
        }
        return false;
	}
	// Return the value of "_sender_message_separation"
    std::string sender_message_separation () {return __sender_message_separation;};
	// Change the value of the static "__can_print" variable.
    void set_can_print(bool new_can_print) { __can_print = new_can_print; };
	// Change the value of the static "_sender_message_separation" variable.
    void set_sender_message_separation(std::string new_sender_message_separation) { __sender_message_separation = new_sender_message_separation; };
	// Change the value of the static "_type_sender_separation" variable.
    void set_type_sender_separation(std::string new_type_sender_separation) { __type_sender_separation = new_type_sender_separation; };
	// Return the value of "_type_sender_separation"
    std::string type_sender_separation () {return __type_sender_separation;};

    //*********
	//
	// Datas structures manipulation
	//
	//*********

	// Swap a char array
    void swap_char_array(char* array, unsigned int array_size) {
		for (int i = 0; i < floor(array_size / 2.0); i++) {
			char temp = array[i];
			array[i] = array[array_size - (i + 1)];
			array[array_size - (i + 1)] = temp;
		}
	};

    //*********
	//
	// Time handling
	//
	//*********

	// Returns the number of milliseconds since a long date
    long long time_ns() {
	    timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return static_cast<long long>(ts.tv_nsec) + static_cast<long long>(ts.tv_sec) * 1000000000;
	};
}
