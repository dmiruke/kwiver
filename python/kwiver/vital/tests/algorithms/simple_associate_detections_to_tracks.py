# ckwg +29
# Copyright 2019 by Kitware, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
#  * Neither name of Kitware, Inc. nor the names of any contributors may be used
#    to endorse or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
from __future__ import print_function

from kwiver.vital.algo import AssociateDetectionsToTracks
from kwiver.vital.types import DetectedObjectSet, ObjectTrackSet, Timestamp
from kwiver.vital.types import ImageContainer

import numpy as np

class SimpleAssociateDetectionsToTracks(AssociateDetectionsToTracks):
    """
    Implementation of AssociateDetectionsToTrack to test it

    Examples:
    """
    def __init__(self):
        AssociateDetectionsToTracks.__init__(self)
        self.threshold = 0.0

    def get_configuration(self):
        # Inherit from the base class
        cfg = super(AssociateDetectionsToTracks, self).get_configuration()
        cfg.set_value( "threshold", str(self.threshold) )
        return cfg

    def set_configuration( self, cfg_in ):
        cfg = self.get_configuration()
        cfg.merge_config(cfg_in)
        self.threshold     = float(cfg.get_value("threshold"))

    def check_configuration( self, cfg):
        if cfg.has_value("threshold") and \
           not float(cfg.get_value("threshold"))==self.threshold:
            return False
        else:
            return True

    def associate(self, timestamp, image, tracks, detections, cost_matrix,
                  output, unused):
        return True

def __vital_algorithm_register__():
    from kwiver.vital.algo import algorithm_factory
    # Register Algorithm
    implementation_name  = "SimpleAssociateDetectionsToTracks"
    if algorithm_factory.has_algorithm_impl_name(
                            SimpleAssociateDetectionsToTracks.static_type_name(),
                            implementation_name):
        return
    algorithm_factory.add_algorithm( implementation_name,
                                "test simple associate detections to tracks",
                                 SimpleAssociateDetectionsToTracks )
    algorithm_factory.mark_algorithm_as_loaded( implementation_name )
