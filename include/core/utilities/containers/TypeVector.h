#ifndef TYPE_VECTOR_H
#define TYPE_VECTOR_H

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "core/Types.h"

namespace Core {
    template<typename T>
    class TypeVector {
    public:
        TypeVector(size_t capacity = DEFAULT_CAPACITY) {
            reserve(capacity);
        }

        template<typename U, typename... Args>
        void add(Args&&... args) {
            std::type_index type = typeid(U);
            if (typeToIndex.find(type) == typeToIndex.end()) {
                typeToIndex.emplace(type, size());
                indexToType.emplace_back(type);
                elements.push_back(std::make_shared<U>(std::forward<Args>(args)...));
            }
            else {
                // error
            }
        }

        template<typename U>
        void remove() {
            std::type_index type = typeid(U);
            if (typeToIndex.find(type) != typeToIndex.end()) {
                size_t index = typeToIndex[type];
                if (index < size() - 1) {
                    const std::type_index lastType = indexToType.back();
                    elements[index] = std::move(elements.back());
                    indexToType[index] = lastType;
                    typeToIndex.erase(lastType);
                    typeToIndex[lastType] = index;
                }
                elements.pop_back();
                indexToType.pop_back();
                typeToIndex.erase(type);
            }
            else {
                // warning rien n'a enlevé
            }
        }

        void reserve(size_t size) {
            elements.reserve(size);
            indexToType.reserve(size);
            typeToIndex.reserve(size);
        }

        size_t size() {
            return elements.size();
        }

        size_t capacity() {
            return elements.capacity();
        }

        template<typename U>
        std::weak_ptr<T>& get () {
            std::type_index type = typeid(U);
            return elements.at(typeToIndex[type]);
        }

        std::weak_ptr<T>& getLast() {
            return elements.back();
        }

        std::vector<std::shared_ptr<T>>& getAll() {
            return elements;
        }

    private:
        std::vector<std::shared_ptr<T>> elements;
        std::vector<std::type_index> indexToType;
        std::unordered_map<std::type_index, size_t> typeToIndex;
    };
}

#endif //TYPE_VECTOR_H