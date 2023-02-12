源代码：
            // seems a bit wrong here
            const T *operator->() const
            {
                std::cout << "*operator->()" << std::endl;
                return (const T *)value;
            }
报错：
/home/scapy/extdisk/vsomeip_v3/sovp_adaptive_autosar/BSW/sovp-autosar-md-core/core-types/include/sovpap/core/result.h:263:24: error: invalid cast from type ‘const value_type’ {aka ‘const std::__cxx11::basic_string<char>’} to type ‘const std::__cxx11::basic_string<char>*’
  263 |                 return (const T *)value;

源代码：
            const T &ValueOrThrow() const &noexcept(false)
            {
                if (has_value)
                    return value;
                else
                    error.ThrowAsException();
            }

报错：
/home/scapy/extdisk/vsomeip_v3/sovp_adaptive_autosar/BSW/sovp-autosar-md-core/core-types/include/sovpap/core/result.h:344:43: error: control reaches end of non-void function [-Werror=return-type]
  344 |                     error.ThrowAsException();
