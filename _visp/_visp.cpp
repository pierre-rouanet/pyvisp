#include <boost/python.hpp>

#include "CVBoostConverter.hpp"

#include "detector.h"

static void init_ar()
{
    Py_Initialize();
    import_array();
}

BOOST_PYTHON_MODULE(_visp)
{
    using namespace boost::python;

    //initialize converters
    init_ar();

    to_python_converter<cv::Mat,
                        bcvt::matToNDArrayBoostConverter>();
    bcvt::matFromNDArrayBoostConverter();


  // QrCode Detection
  class_<QRCode>("QRCode")
    .def_readonly("polygon", &QRCode::polygon)
    .def_readonly("message", &QRCode::message)
    .def_readonly("cog", &QRCode::cog)
    .def_readonly("bounding_box", &QRCode::bounding_box)
  ;

  class_<DetectorQRCode>("DetectorQRCode")
    .def("detect", &DetectorQRCode::detect)
  ;
}
