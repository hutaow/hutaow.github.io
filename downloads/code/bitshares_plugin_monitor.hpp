/*
 * Copyright (c) 2015 Wang Tao (hutaow@hotmail.com), Inc., and contributors.
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
#pragma once

#include <graphene/app/plugin.hpp>

namespace graphene { namespace monitor_plugin {
    #define MONITOR_ACTION_TYPE_ALL (0xFFFFFFFF)

    class monitor_plugin : public graphene::app::plugin {
        public:
            // 插件名称
            std::string plugin_name()const override;

            // 插件描述信息
            std::string plugin_description()const override;

            // 配置参数注册
            virtual void plugin_set_program_options(
                boost::program_options::options_description &command_line_options,
                boost::program_options::options_description &config_file_options
            ) override;

            // 插件初始化
            virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;

            // 启动插件
            virtual void plugin_startup() override;

            // 停止插件
            virtual void plugin_shutdown() override;

        private:
            // 事件注册句柄
            boost::signals2::connection monitor_signed_block_handler;
            boost::signals2::connection monitor_signed_trans_handler;

            // 监控事件类型（暂时未使用）
            uint32_t monitor_action_type = MONITOR_ACTION_TYPE_ALL;

            // 生成区块事件回调函数
            void monitor_signed_block( const graphene::chain::signed_block& b);

            // 生成交易信息事件回调函数
            void monitor_pending_transaction( const graphene::chain::signed_transaction& trans);
    };
} } // graphene::monitor_plugin
