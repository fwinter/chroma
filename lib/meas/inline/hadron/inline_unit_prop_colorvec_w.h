// -*- C++ -*-
// $Id: inline_unit_prop_colorvec_w.h,v 1.1 2008-10-28 21:34:47 edwards Exp $
/*! \file
 * \brief Construct a propagator element that is     I^-1 * multi1d<LatticeColorVector>
 *
 * Test setup for a unit matrix applied to a colorvector.
 * The structure makes it look like a prop_colorvector
 */

#ifndef __inline_unit_prop_colorvec_w_h__
#define __inline_unit_prop_colorvec_w_h__

#include "chromabase.h"
#include "meas/inline/abs_inline_measurement.h"
#include "io/qprop_io.h"

namespace Chroma 
{ 
  /*! \ingroup inlinehadron */
  namespace InlineUnitPropColorVecEnv 
  {
    bool registerAll();

    //! Parameter structure
    /*! \ingroup inlinehadron */ 
    struct Params 
    {
      Params();
      Params(XMLReader& xml_in, const std::string& path);

      unsigned long     frequency;

      struct Param_t
      {
	struct Contract_t
	{
	  int num_vecs;             /*!< Number of color vectors to use */
	  int decay_dir;            /*!< Decay direction */
	  multi1d<int> t_sources;   /*!< Array of time slice sources for props */
	};

	Contract_t      contract;
      } param;

      struct NamedObject_t
      {
	std::string     gauge_id;       /*!< Gauge field */
	std::string     colorvec_id;    /*!< LatticeColorVector EigenInfo */
	std::string     prop_id;        /*!< Id for output propagator solutions */
      } named_obj;

      std::string xml_file;  // Alternate XML file pattern
    };


    //! Inline task for compute LatticeColorVector matrix elements of a propagator
    /*! \ingroup inlinehadron */
    class InlineMeas : public AbsInlineMeasurement 
    {
    public:
      ~InlineMeas() {}
      InlineMeas(const Params& p) : params(p) {}
      InlineMeas(const InlineMeas& p) : params(p.params) {}

      unsigned long getFrequency(void) const {return params.frequency;}

      //! Do the measurement
      void operator()(const unsigned long update_no,
		      XMLWriter& xml_out); 

    protected:
      //! Do the measurement
      void func(const unsigned long update_no,
		XMLWriter& xml_out); 

    private:
      Params params;
    };

  } // namespace PropColorVec


}

#endif
