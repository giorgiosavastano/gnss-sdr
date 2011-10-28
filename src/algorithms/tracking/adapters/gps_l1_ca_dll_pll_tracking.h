/*!
 * \file gnss_correlator_a.h
 * \brief Brief description of the file here
 * \author Javier Arribas, 2011. jarribas(at)cttc.es
 *
 * Detailed description of the file here if needed.
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2011  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */


#ifndef GPS_L1_CA_DLL_PLL_TRACKING_H_
#define GPS_L1_CA_DLL_PLL_TRACKING_H_

#include "tracking_interface.h"

#include "gps_l1_ca_dll_pll_tracking_cc.h"

#include <gnuradio/gr_msg_queue.h>

class ConfigurationInterface;


class GpsL1CaDllPllTracking : public TrackingInterface
{

public:

  GpsL1CaDllPllTracking(ConfigurationInterface* configuration,
            std::string role,
            unsigned int in_streams,
            unsigned int out_streams,
            gr_msg_queue_sptr queue);

    virtual ~GpsL1CaDllPllTracking();

    std::string role()
    {
        return role_;
    }
    std::string implementation()
    {
        return "tracking";
    }
    size_t item_size()
    {
        return item_size_;
    }

    void connect(gr_top_block_sptr top_block);
    void disconnect(gr_top_block_sptr top_block);
    gr_basic_block_sptr get_left_block();
    gr_basic_block_sptr get_right_block();

    void set_satellite(unsigned int satellite);
    void set_channel(unsigned int channel);
    void set_prn_code_phase(signed int phase);
    void set_doppler_freq_shift(float phase);
    void set_channel_queue(concurrent_queue<int> *channel_internal_queue);

    void start_tracking();

    void set_acq_sample_stamp(unsigned long int sample_stamp);

private:

    gps_l1_ca_dll_pll_tracking_cc_sptr tracking_;
    size_t item_size_;
    std::string item_type_;
    unsigned int vector_length_;
    unsigned int satellite_;
    unsigned int channel_;
    long fs_in_;
    long if_;
    bool dump_;
    std::string dump_filename_;

    std::string role_;
    unsigned int in_streams_;
    unsigned int out_streams_;
    gr_msg_queue_sptr queue_;
    concurrent_queue<int> *channel_internal_queue_;
};

#endif // GPS_L1_CA_DLL_PLL_TRACKING_H_