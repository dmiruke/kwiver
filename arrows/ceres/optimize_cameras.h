/*ckwg +29
 * Copyright 2016 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
* \file
* \brief Header defining Ceres algorithm implementation of camera optimization.
*/

#ifndef KWIVER_ARROWS_CERES_OPTIMIZE_CAMERAS_H_
#define KWIVER_ARROWS_CERES_OPTIMIZE_CAMERAS_H_

#include <vital/vital_config.h>
#include <arrows/ceres/kwiver_algo_ceres_export.h>

#include <vital/algo/optimize_cameras.h>

#include <memory>

namespace kwiver {
namespace arrows {
namespace ceres {

/// A class for optimization of camera paramters using Ceres
class KWIVER_ALGO_CERES_EXPORT optimize_cameras
: public vital::algorithm_impl<optimize_cameras, vital::algo::optimize_cameras>
{
public:
  /// Constructor
  optimize_cameras();

  /// Destructor
  virtual ~optimize_cameras();

  /// Copy Constructor
  optimize_cameras(const optimize_cameras& other);

  /// Return the name of this implementation
  virtual std::string impl_name() const { return "ceres"; }

  /// Get this algorithm's \link vital::config_block configuration block \endlink
  virtual vital::config_block_sptr get_configuration() const;
  /// Set this algorithm's properties via a config block
  virtual void set_configuration(vital::config_block_sptr config);
  /// Check that the algorithm's currently configuration is valid
  virtual bool check_configuration(vital::config_block_sptr config) const;

  using vital::algo::optimize_cameras::optimize;

  /// Optimize a single camera given corresponding features and landmarks
  /**
   * This function assumes that 2D features viewed by this camera have
   * already been put into correspondence with 3D landmarks by aligning
   * them into two parallel vectors
   *
   * \param[in,out] camera    The camera to optimize.
   * \param[in]     features  The vector of features observed by \p camera
   *                          to use as constraints.
   * \param[in]     landmarks The vector of landmarks corresponding to
   *                          \p features.
   */
  virtual void
  optimize(vital::camera_sptr & camera,
           const std::vector<vital::feature_sptr>& features,
           const std::vector<vital::landmark_sptr>& landmarks) const;

private:
  /// private implementation class
  class priv;
  const std::unique_ptr<priv> d_;
};


} // end namespace ceres
} // end namespace arrows
} // end namespace kwiver

#endif // KWIVER_ARROWS_CERES_OPTIMIZE_CAMERAS_H_
