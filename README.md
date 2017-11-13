# tagged
Strong typedef for C++

Unlike many other strong typedefs, this supports implicit conversion between tagged types with the same tag, but a different underlying type.
This feature also allows you to create tagged objects that contain a reference to an underlying type.

```C++
using meter = tagged<double, struct meter_tag>;

void print_meter(meter::cref m)
{
	std::cout << m.value() << "m" << std::endl;
}

int main()
{
	// passing a value of the underlying type with in a strongly typed way without copies
	int distance = 4;
	print_meter(as_ref<meter>(distance));

	using seconds = tagged<double, struct seconds_tag>;
	auto time = seconds(3.3);
	// print_meter(time); -> does not compile
}
```

It does at the moment not support iostreams or other operations.
