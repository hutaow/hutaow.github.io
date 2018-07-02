/*
 * Copyright (c) 2018 Wang Tao (hutaow@hotmail.com), and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <graphene/monitor/monitor.hpp>
#include <graphene/chain/database.hpp>
#include <fc/io/fstream.hpp>
#include <iostream>

using namespace graphene::monitor_plugin;
using namespace graphene::chain;
using namespace std;

#define MONITOR_OPT_ACTION_TYPE "monitor-action-type"

void monitor_plugin::plugin_set_program_options(
   boost::program_options::options_description& command_line_options,
   boost::program_options::options_description& config_file_options)
{
   command_line_options.add_options()
         (MONITOR_OPT_ACTION_TYPE, boost::program_options::value<uint32_t>(), "The type of operation monitored")
         ;
   config_file_options.add(command_line_options);
}

std::string monitor_plugin::plugin_name()const
{
    return "monitor";
}

std::string monitor_plugin::plugin_description()const
{
    return "Monitor transaction status.";
}

void monitor_plugin::plugin_initialize(const boost::program_options::variables_map& options) {
    try {
        ilog("monitor plugin: plugin_initialize() begin");
        
        // 读取参数配置
        if (options.count(MONITOR_OPT_ACTION_TYPE)) {
            monitor_action_type = options[MONITOR_OPT_ACTION_TYPE].as<uint32_t>();
        } else {
            monitor_action_type = MONITOR_ACTION_TYPE_ALL;
        }

        ilog("monitor plugin: plugin_initialize() end");
    } FC_LOG_AND_RETHROW()

    return;
}

void monitor_plugin::plugin_startup() {
    // 注册事件回调函数
    monitor_signed_block_handler = database().applied_block.connect( [&]( const graphene::chain::signed_block& blk ) {
        monitor_signed_block(blk);
    });

    return;
}

void monitor_plugin::plugin_shutdown() {
    // 卸载事件回调函数
    database().applied_block.disconnect(monitor_signed_block_handler);

    return;
}

void monitor_plugin::monitor_signed_block(const graphene::chain::signed_block& blk) {
    for (uint32_t i = 0; i < blk.transactions.size(); ++i) {
        processed_transaction trans = blk.transactions[i];

        for (uint32_t j = 0; j < trans.operations.size(); ++j) {
            operation op = trans.operations[j];

            if (operation::tag<transfer_operation>::value == op.which()) {
                transfer_operation& op_trans = op.get<transfer_operation>();
                const account_object& from_account = op_trans.from(database());
                const account_object& to_account = op_trans.to(database());
                const asset_object& asset_type = op_trans.amount.asset_id(database());

                cout<<">>> action transfer: "<< from_account.name << " -> " << to_account.name << " "
                    << asset_type.amount_to_pretty_string(op_trans.amount) << endl;
            }
        }
    }
    return;
}
