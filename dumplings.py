'''Generate huge file for testing purpose'''

class GenExampleFile:
    def __init__(self, N : 10):
        self.N = N
        self.listOfConditions = []

    @staticmethod
    def number_to_letter(number):
        """Function support element name generation 
        e.x. element 111 will be translate into BBB,
        usable for ex. as class name. """

        translate_map = {
            '0': 'A',
            '1': 'B',
            '2': 'C',
            '3': 'D',
            '4': 'E',
            '5': 'F',
            '6': 'G',
            '7': 'H',
            '8': 'I',
            '9': 'J',
        }

        result = ''
        
        for element in number:
            if element in translate_map:
                result += translate_map[element]
            else:
                result += "?" #Add Exeption handle..

        return result

    @staticmethod
    def add_header(header="<type_traits>"):
        return "#include " + header

    @staticmethod
    def function_template_2017_1(name="AAA"):
        """Function substitute function/class name in defined strings"""

        temp_func = f"""
template <typename T>
std::enable_if_t<std::is_arithmetic_v<T> && std::is_unsigned_v<T>, T> {name}(T a, T b)
{{
    return (a > b) ? a : b;
}}
"""     
        return temp_func
    
    @staticmethod
    def function_template_2017_2(name="AAA"):
        """Function substitute function/class name in defined strings"""

        temp_func = f"""
template <typename T>
std::enable_if_t<std::is_same_v<T, std::string>>
{name}(T a)
{{
    std::string r = a;
    return r;
}}
"""     
        return temp_func
    
    @staticmethod
    def function_template_2017_3(name="AAA"):
        """Function substitute function/class name in defined strings"""

        temp_func = f"""
template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, T>::type
{name}(T a, T b, T c)
{{
    return a + b + c;
}}
"""     
        return temp_func
    

    @staticmethod
    def function_template_2020_1(name="AAA"):
        """Function substitute function/class name in defined strings"""
        
        temp_func = f"""
template <typename T>
requires std::is_arithmetic_v<T> && std::is_unsigned_v<T>
T {name}(T a, T b)
{{
    return (a > b) ? a : b;
}}
"""
        return temp_func

    @staticmethod
    def function_template_2020_2(name="AAA"):
        """Function substitute function/class name in defined strings"""
        
        temp_func = f"""
template <typename T>
requires std::is_same_v<T, std::string>
std::string {name}(T a)
{{
    std::string r = a;
    return r;
}}
"""
        return temp_func
    
    @staticmethod
    def function_template_2020_3(name="AAA"):
        """Function substitute function/class name in defined strings"""
        
        temp_func = f"""
template <typename T>
requires std::integral<T> && std::signed_integral<T>
T {name}(T a, T b, T c)
{{
    return a + b + c;
}}
"""
        return temp_func
    
    def function_template_usage_1(self,number,param_1="(unsigned)4", param_2="(unsigned)2"):
        result = f"\n{self.number_to_letter(number)}({param_1},{param_2});"
        return result
    
    def function_template_usage_2(self,number,param_1="(std::string)\"std::string\""):
        result = f"\nstd::string {self.number_to_letter(number)}({param_1});"
        return result
    
    def function_template_usage_3(self,number,param_1=1, param_2=2, param_3=3):
        result = f"\n{self.number_to_letter(number)}<int>({param_1},{param_2},{param_3});"
        return result



    def gen_file_2017_1(self):
        with open('test_file_2017_1.cpp', 'w') as file:
            header = self.add_header()
            file.write(header)
            file.write("\n")

        with open('test_file_2017_1.cpp', 'a') as file:
            for i in range(self.N):
                named_template = self.function_template_2017_1(self.number_to_letter(str(i)))
                file.write(named_template)

        with open('test_file_2017_1.cpp', 'a') as file:
            file.write("\nint main(){")
            for i in range(self.N):
                tmp_use = self.function_template_usage_1(str(i))
                file.write(tmp_use)
            file.write("\n}")

    def gen_file_2017_2(self):
        with open('test_file_2017_2.cpp', 'w') as file:
            header_1 = self.add_header("<type_traits>")
            header_2 = self.add_header("<string>")
            file.write(header_1)
            file.write("\n")
            file.write(header_2)
            file.write("\n")

        with open('test_file_2017_2.cpp', 'a') as file:
            for i in range(self.N):
                named_template = self.function_template_2017_2(self.number_to_letter(str(i)))
                file.write(named_template)

        with open('test_file_2017_2.cpp', 'a') as file:
            file.write("\nint main(){")
            for i in range(self.N):
                tmp_use = self.function_template_usage_2(str(i))
                file.write(tmp_use)
            file.write("\n}")

    def gen_file_2017_3(self):
        with open('test_file_2017_3.cpp', 'w') as file:
            header = self.add_header("<type_traits>")
            file.write(header)
            file.write("\n")

        with open('test_file_2017_3.cpp', 'a') as file:
            for i in range(self.N):
                named_template = self.function_template_2017_3(self.number_to_letter(str(i)))
                file.write(named_template)

        with open('test_file_2017_3.cpp', 'a') as file:
            file.write("\nint main(){")
            for i in range(self.N):
                tmp_use = self.function_template_usage_3(str(i))
                file.write(tmp_use)
            file.write("\n}")

    def gen_file_2020_1(self):
        with open('test_file_2020_1.cc', 'w') as file:
            header = self.add_header()
            file.write(header)
            file.write("\n")

        with open('test_file_2020_1.cc', 'a') as file:
            for i in range(self.N):
                named_template = self.function_template_2020_1(self.number_to_letter(str(i)))
                file.write(named_template)

        with open('test_file_2020_1.cc', 'a') as file:
            file.write("\nint main(){")
            for i in range(self.N):
                tmp_use = self.function_template_usage_1(str(i))
                file.write(tmp_use)
            file.write("\n}")

    def gen_file_2020_2(self):
        with open('test_file_2020_2.cc', 'w') as file:
            header_1 = self.add_header("<type_traits>")
            header_2 = self.add_header("<string>")
            file.write(header_1)
            file.write("\n")
            file.write(header_2)
            file.write("\n")

        with open('test_file_2020_2.cc', 'a') as file:
            for i in range(self.N):
                named_template = self.function_template_2020_2(self.number_to_letter(str(i)))
                file.write(named_template)

        with open('test_file_2020_2.cc', 'a') as file:
            file.write("\nint main(){")
            for i in range(self.N):
                tmp_use = self.function_template_usage_2(str(i))
                file.write(tmp_use)
            file.write("\n}")        

    def gen_file_2020_3(self):
        with open('test_file_2020_3.cc', 'w') as file:
            header = self.add_header("<concepts>")
            file.write(header)
            file.write("\n")
            pass

        with open('test_file_2020_3.cc', 'a') as file:
            for i in range(self.N):
                named_template = self.function_template_2020_3(self.number_to_letter(str(i)))
                file.write(named_template)

        with open('test_file_2020_3.cc', 'a') as file:
            file.write("\nint main(){")
            for i in range(self.N):
                tmp_use = self.function_template_usage_3(str(i))
                file.write(tmp_use)
            file.write("\n}")       



def main():
    generator = GenExampleFile(10000)
    generator.gen_file_2017_1()
    generator.gen_file_2020_1()
    generator.gen_file_2017_2()
    generator.gen_file_2020_2()
    generator.gen_file_2017_3()
    generator.gen_file_2020_3()

    return 0


if __name__ == "__main__":
    main()








