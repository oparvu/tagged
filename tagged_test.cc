#include "tagged.h"
#include <iostream>
#include <string>

using meter = tagged_type::tagged<double, struct meter_tag>;

void take_meter(meter distance)
{
	meter d = distance;
}

void take_by_ref(meter::ref distance)
{
	distance.value() = 1.1;
}

void take_by_cref(meter::cref distance)
{
	std::cout << distance.value() << "m" << std::endl;
}

void test()
{
	auto distance = meter{1.1};
	take_meter(distance);
	take_meter(tagged_type::as<meter>(5));
	take_meter(tagged_type::as_ref<meter>(5));
	int ivalue = 5;
	double dvalue = 2.2;
	meter::ref d{distance};
	take_by_ref(distance);
//	take_by_ref(tagged_type::as_ref<meter>(ivalue)); // should not work
	take_by_ref(tagged_type::as_ref<meter>(dvalue));
//	take_by_ref(tagged_type::as<meter>(5)); // should not work
//	take_by_ref(tagged_type::as_ref<meter>(5)); // should not work
	take_by_cref(distance);
	take_by_cref(tagged_type::as_ref<meter>(dvalue));
	take_by_cref(tagged_type::as_ref<meter>(ivalue));
	take_by_cref(tagged_type::as<meter>(5));
	take_by_cref(tagged_type::as_ref<meter>(5));

	{
		meter m;
		meter::ref mr{dvalue};
		meter::cref mcr{dvalue};
		m = m;
		m = mr;
		m = mcr;
//		mr = m;
//		mr = mr;
//		mr = mcr;
//		mcr = m;
//		mcr = mr;
//		mcr = mcr;
		m = std::move(m);
		m = std::move(mr);
		m = std::move(mcr);
//		mr = std::move(m);
//		mr = std::move(mr);
//		mr = std::move(mcr);
//		mcr = std::move(m);
//		mcr = std::move(mr);
//		mcr = std::move(mcr);
		meter m1 = m;
		meter m2 = mr;
		meter m3 = mcr;
		meter::ref mr1 = m;
		meter::ref mr2 = mr;
//		meter::ref mr3 = mcr;
		meter::cref mcr1 = m;
		meter::cref mcr2 = mr;
		meter::cref mcr3 = mcr;
	}
	{
		meter const m;
		meter::ref const mr{dvalue};
		meter::cref const mcr{dvalue};
		meter m1 = m;
		meter m2 = mr;
		meter m3 = mcr;
//		meter::ref mr1 = m;
		meter::ref mr2 = mr; // this works because mr is not 'T const&' but 'T& const'
//		meter::ref mr3 = mcr;
		meter::cref mcr1 = m;
		meter::cref mcr2 = mr;
		meter::cref mcr3 = mcr;
	}
}

int main()
{
	test();
}
