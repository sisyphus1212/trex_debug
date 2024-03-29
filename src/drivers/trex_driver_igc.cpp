/*
  TRex team
  Cisco Systems, Inc.
*/

/*
  Copyright (c) 2015-2017 Cisco Systems, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "trex_driver_igc.h"
#include "trex_driver_defines.h"
#include "dpdk/drivers/net/igc/base/igc_regs.h"
#include "dpdk/drivers/net/igc/igc_filter.h"
//#include "dpdk/drivers/net/ixgbe/base/ixgbe_type.h"
#include "trex_rte_eth_ctrl.h"


// tmp no rss for debug.
CTRexExtendedDriverBase2500M::CTRexExtendedDriverBase2500M() {
    m_cap = tdCAP_ONE_QUE | tdCAP_MULTI_QUE | TREX_DRV_CAP_MAC_ADDR_CHG;
}

TRexPortAttr* CTRexExtendedDriverBase2500M::create_port_attr(tvpid_t tvpid,repid_t repid) {
    return new DpdkTRexPortAttr(tvpid, repid, false, true, false, false, false);
}

int CTRexExtendedDriverBase2500M::get_min_sample_rate(void){
    return (RX_CHECK_MIX_SAMPLE_RATE);
}

void CTRexExtendedDriverBase2500M::update_configuration(port_cfg_t * cfg){
    cfg->m_tx_conf.tx_thresh.pthresh = TX_PTHRESH;
    cfg->m_tx_conf.tx_thresh.hthresh = TX_HTHRESH;
    cfg->m_tx_conf.tx_thresh.wthresh = TX_WTHRESH;
}

bool CTRexExtendedDriverBase2500M::is_support_for_rx_scatter_gather(){
    if (get_is_tcp_mode()) {
        return (false);
    }
    return (true);
}

