// -*- C++ -*-
// $Id: inline_prop_matelem_colorvec_w.h,v 1.1 2008-06-17 17:46:45 edwards Exp $
/*! \file
 * \brief Compute the matrix element of  LatticeColorVector*M^-1*LatticeColorVector
 *
 * Propagator calculation on a colorvector
 */

#ifndef __inline_prop_matelem_colorvec_w_h__
#define __inline_prop_matelem_colorvec_w_h__

#include "chromabase.h"
#include "meas/inline/abs_inline_measurement.h"
#include "io/qprop_io.h"

namespace Chroma 
{ 
  /*! \ingroup inlinehadron */
  namespace InlinePropMatElemColorVecEnv 
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
	  int num_vecs;   /*!< Number of color vectors to use */
	  int t_source;   /*!< Time slice source for props */
	  int decay_dir;  /*!< Decay direction */
	};

	ChromaProp_t    prop;
	Contract_t      contract;
      } param;

      struct NamedObject_t
      {
	std::string     gauge_id;
	std::string     source_id;
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

  } // namespace PropMatElemColorVec


  //! Reader
  /*! \ingroup inlinehadron */
  void read(XMLReader& xml, const string& path, InlinePropMatElemColorVecEnv::Params& param);

  //! Writer
  /*! \ingroup inlinehadron */
  void write(XMLWriter& xml, const string& path, const InlinePropMatElemColorVecEnv::Params& param);


}

#endif
