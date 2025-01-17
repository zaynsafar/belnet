#pragma once

#include <llarp/dht/key.hpp>
#include <llarp/router_id.hpp>
#include <llarp/util/aligned.hpp>

#include <functional>
#include <numeric>
#include <string>
#include <string_view>
#include <variant>
#include <set>

namespace llarp
{
  namespace service
  {
    /// Snapp Address
    struct Address : public AlignedBuffer<32>
    {
      /// if parsed using FromString this contains the subdomain
      /// this member is not used when comparing it's extra data for dns
      std::string subdomain;

      /// list of whitelisted gtld to permit
      static const std::set<std::string> AllowedTLDs;

      /// return true if we permit using this tld
      /// otherwise return false
      static bool
      PermitTLD(const char* tld);

      std::string
      ToString(const char* tld = ".bdx") const;

      bool
      FromString(std::string_view str, const char* tld = ".bdx");

      Address() : AlignedBuffer<32>()
      {}

      explicit Address(const std::string& str) : AlignedBuffer<32>()
      {
        if (not FromString(str))
          throw std::runtime_error("invalid address");
      }

      explicit Address(const Data& buf) : AlignedBuffer<32>(buf)
      {}

      Address(const Address& other)
          : AlignedBuffer<32>(other.as_array()), subdomain(other.subdomain)
      {}

      explicit Address(const AlignedBuffer<32>& other) : AlignedBuffer<32>(other)
      {}

      bool
      operator<(const Address& other) const
      {
        return as_array() < other.as_array();
      }

      friend std::ostream&
      operator<<(std::ostream& out, const Address& self)
      {
        return out << self.ToString();
      }

      bool
      operator==(const Address& other) const
      {
        return as_array() == other.as_array();
      }

      bool
      operator!=(const Address& other) const
      {
        return as_array() != other.as_array();
      }

      Address&
      operator=(const Address& other) = default;

      dht::Key_t
      ToKey() const;

      RouterID
      ToRouter() const
      {
        return RouterID(as_array());
      }
    };

    std::optional<std::variant<Address, RouterID>>
    ParseAddress(std::string_view belnet_addr);

  }  // namespace service
}  // namespace llarp

namespace std
{
  template <>
  struct hash<llarp::service::Address>
  {
    size_t
    operator()(const llarp::service::Address& addr) const
    {
      return std::accumulate(addr.begin(), addr.end(), 0, std::bit_xor{});
    }
  };
}  // namespace std
