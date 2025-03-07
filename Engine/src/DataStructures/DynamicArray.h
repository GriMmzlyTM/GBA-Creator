//
// Created by elito on 7/24/2024.
//

#pragma once

namespace DataStructures {


    /// Dynamically sized array.
    ///
    /// When this array's size is reached it automatically expands.
    /// A DynamicArray is JUST an array. It does not sort your data in any way. This means a DynamicArray has the same
    /// performance as a regular array;
    /// Use this for performance-critical logic, or when you need your data to maintain its index as well as fast insert times.
    /// \tparam TDataType The data stored in the array
    template<typename TDataType>
    class DynamicArray {
        TDataType* _array;
        int _size;

    public:

        DynamicArray(int Capacity) {

        }

        inline int Size() {
            return _size;
        };



    };

} // DataStructures
