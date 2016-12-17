//
// Created by aguado_e on 12/5/16.
//

#ifndef R_TYPE_SERIALIZATIONHELPER_HPP
#define R_TYPE_SERIALIZATIONHELPER_HPP

#include <iostream>
#include <assert.h>
#include <climits>

namespace RType {
    class SerializationHelper {
    public:

        static bool _IsBigEndian()
        {
            short int i = 0x0102;
            char b[2];
            *(short int *) (b) = i;
            return b[0] == 1;
        }

        template<typename T>
        static T SwapEndian(T u) {
            static_assert(CHAR_BIT == 8, "Char size != 8. Can't perform serialization.");
            union {
                T u;
                unsigned char u8[sizeof(T)];
            } source, dest;
            source.u = u;
            for (size_t k = 0; k < sizeof(T); k++)
                dest.u8[k] = source.u8[sizeof(T) - k - 1];
            return dest.u;
        }

        template<typename Ttype>
        static void Serialize(char *buffer, uint16_t index, Ttype &value) {
            if (RType::SerializationHelper::_IsBigEndian()) {
                if (sizeof(Ttype) == 1) // 1 byte => no swap needed
                    *((Ttype *) (buffer + index)) = value;

                else if (sizeof(Ttype) == 2) // 2 bytes
                    *((Ttype *) (buffer + index)) = SwapEndian(value);

                else if (sizeof(Ttype) == 4) // 4 bytes
                    *((Ttype *) (buffer + index)) = SwapEndian(value);

                else if (sizeof(Ttype) == 8) // 8 bytes
                    *((Ttype *) (buffer + index)) = SwapEndian(value);
            } else
                *((Ttype *) (buffer + index)) = value;
        }

        template<typename Ttype>
        static void Deserialize(char *buffer, uint16_t index, Ttype &value) {
            value = *((Ttype *) (buffer + index));
        }
    };
}


#endif //R_TYPE_SERIALIZATIONHELPER_HPP
