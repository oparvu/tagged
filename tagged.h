#pragma once
#include <type_traits>
#include <utility>

namespace tagged_type {

	template<typename T, typename TAG>
	struct tagged
	{
		using tag = TAG;
		template<typename... Args>
		explicit tagged(Args&&... args)	: _value(std::forward<Args>(args)...) {}

		template<typename from_type, typename = std::enable_if_t<std::is_constructible_v<T, from_type const&>>>
		tagged(tagged<from_type, tag> const& tag) : _value(tag.value()) {}

		template<typename from_type, typename = std::enable_if_t<std::is_constructible_v<T, from_type&>>>
		tagged(tagged<from_type, tag>& tag) : _value(tag.value()) {}

		template<typename from_type, typename = std::enable_if_t<std::is_constructible_v<T, from_type&&>>>
		tagged(tagged<from_type, tag>&& tag) : _value(std::move(tag.value()))
		{
			static_assert(
				!std::is_reference_v<T> ||
				(std::is_reference_v<from_type> &&
				 std::is_same_v<std::decay_t<T>, std::decay_t<from_type>>)
						, "Cannot take reference to temporary");
		}

		T const& value() const& { return _value; }
		T& value() & { return _value; }
		T&& value() const&& { return std::move(_value); }

		using ref = tagged<T&, tag>;
		using cref = tagged<T const&, tag>;

	private:
		T _value;
	};

	template<typename strong_type, typename T>
	auto as(T ref)
	{
		return tagged<T, typename strong_type::tag>{std::move(ref)};
	}

	template<typename strong_type, typename T>
	auto as_ref(T&& ref)
	{
		return tagged<T&, typename strong_type::tag>{ref};
	}

}
