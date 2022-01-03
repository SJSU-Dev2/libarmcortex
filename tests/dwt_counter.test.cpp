#include <boost/ut.hpp>
#include <libarmcortex/dwt_counter.hpp>

namespace embed::cortex_m {
boost::ut::suite dwt_test = []() {
  using namespace boost::ut;
  using namespace embed::cortex_m;

  dwt_counter test_subject;

  "dwt_counter::start()"_test = [&]() {
    test_subject.initialize();

    expect(that % cortex_m::dwt_counter::core_trace_enable ==
           cortex_m::dwt_counter::core->demcr);
  };

  /*
  expect(that % 0 == cortex_m::dwt_counter::dwt->cyccnt);
  expect(that % cortex_m::dwt_counter::enable_cycle_count ==
          cortex_m::dwt_counter::dwt->ctrl);
  */

  "dwt_counter::count()"_test = [&]() {
    cortex_m::dwt_counter::dwt->cyccnt = 0;
    expect(that % 0 == test_subject.count().value());
    cortex_m::dwt_counter::dwt->cyccnt = 17;
    expect(that % 17 == test_subject.count().value());
    cortex_m::dwt_counter::dwt->cyccnt = 1024;
    expect(that % 1024 == test_subject.count().value());
  };
};
}
