#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

namespace oneCC::CodeGenerator::Aarch32 {

class VarManager {
public:
    VarManager() = default;

    // Offset shows where in stack var is stored.
    // Returns 0 on success.
    int setOffset(int varId, int offset) { m_offsetStorage[varId] = offset; return 0; }
    int setOffset(const std::string& alias, int offset)
    {
        if (getId(alias) == 0) {
            return -1;
        }
        m_offsetStorage[getId(alias)] = offset;
        return 0;
    }

    int getOffset(int varId) { return m_offsetStorage[varId]; }
    int getOffset(const std::string& alias) { return m_offsetStorage[getId(alias)]; }
    
    int addVariable(const std::string& alias)
    { 
        m_idStorage[std::make_pair(alias, m_level)] = ++m_nextId;
        return m_nextId;
    }
    int getId(const std::string& alias) { return m_idStorage[std::make_pair(alias, m_level)]; }

    void enterScope() { m_level++; }

    void leaveScope()
    {
        auto idStorageEntry = m_idStorage.begin();
        while (m_idStorage.end() != (idStorageEntry = std::find_if(m_idStorage.begin(), m_idStorage.end(), [this](auto p) { return p.first.second == m_level; }))) {
            m_idStorage.erase(idStorageEntry);
            m_offsetStorage.erase(idStorageEntry->second);
        }
        m_level--;
    }

    void dump()
    {
        std::cout << "--- VarManager Storage Dump ---\n";
        for (auto entry : m_idStorage) {
            std::cout << entry.first.first << " " << entry.first.second << ": " << entry.second << " id\n";
        }
        for (auto entry : m_offsetStorage) {
            std::cout << entry.first << " = " << entry.second << "\n";
        }
        std::cout << "--- VarManager Storage End ----\n";
    }

private:
    int m_level { 0 };
    int m_nextId { 0 };
    
    // Key: <var alias, scope level>
    // Value: id
    std::map<std::pair<std::string, int>, int> m_idStorage {};
    
    // Key: id
    // Value: offset in stack (relative frame pointer)
    std::map<int, int> m_offsetStorage {};
};

}