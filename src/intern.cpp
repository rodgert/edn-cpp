// SPDX-License-Identifier: BSL-1.0
#include <edn/value.hpp>

#include <mutex>
#include <unordered_set>

namespace edn::intern {

std::string_view get(std::string_view s) {
    // Function-local statics (Construct On First Use): safe against
    // static initialisation order fiasco — edn::keyword and edn::symbol
    // may be constructed at static-init time by consumers.
    static std::unordered_set<std::string> table;
    static std::mutex                      mu;
    std::lock_guard<std::mutex>            lock(mu);
    auto [it, inserted] = table.emplace(s);
    (void)inserted;
    return *it;
}

} // namespace edn::intern
