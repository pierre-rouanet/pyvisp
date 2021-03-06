#include <png.h>
#include <boost/python.hpp>

#include "CVBoostConverter.hpp"

#include "detector.h"
#include "tracker.h"

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

  class_<VispQRCodeDetector>("QRCodeDetector")
    .def("detect", &VispQRCodeDetector::detect)
  ;

  // Object Tracking
  class_<VispMbObjectTracker>("MbObjectTracker",
                              init<std::string, std::string>())
    .def("init_from_points", &VispMbObjectTracker::initFromPoints)

    .def("track", &VispMbObjectTracker::track)
    .def("get_pose", &VispMbObjectTracker::getPose)
  ;

  // Object Detection
  class_<VispObjectKeypointDetector>("ObjectKeypointDetector",
                                     init<std::string>())
    .def("load_learning_data", &VispObjectKeypointDetector::loadLearningData)
    .def("train_and_save", &VispObjectKeypointDetector::trainAndSave)
    .def("detect", &VispObjectKeypointDetector::detect)
  ;
}
