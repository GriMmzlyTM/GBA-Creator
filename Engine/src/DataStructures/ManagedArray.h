//
// Created by elito on 7/24/2024.
//

#pragma once

#include <vector>
#include <queue>
#include <set>

namespace DataStructures {

    template<typename TDataType>
    class ManagedArray {
        std::vector<TDataType*> _array;
        int _size;

        std::queue<int> _freeIds;
        std::set<int> _allocatedIds;

    public:

        explicit ManagedArray(const int& capacity);
        [[nodiscard]] const std::vector<int>& GetNonNullIndices() const;
        void Clear();
        void ExpandArray();
        int Add();
        void Remove();
        void Get();

        TDataType& operator[](const std::size_t& index)  {
            if (index >= _size) {
                // TODO: Error
                return nullptr;
            }
            return _array[index];

        }

    private:
        const int GenerateIds();

    };

    template<typename TDataType>
    int ManagedArray<TDataType>::Add() {
        return 0;
    }

    template<typename TDataType>
    ManagedArray<TDataType>::ManagedArray(const int &capacity) {
        _size = capacity;

        for (int i = 0; i < capacity; ++i) {
            _freeIds.emplace(i);
        }

    }

    template<typename TDataType>
    const std::vector<int> &ManagedArray<TDataType>::GetNonNullIndices() const {
        std::vector<int> nonNullIndices(_allocatedIds.begin(), _allocatedIds.end());
        return nonNullIndices;
    }

} // DataStructures
