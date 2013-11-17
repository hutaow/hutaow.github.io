" 设置字符编码
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8,ucs-bom,gb2312,gb18030,gbk,cp936

" 设置文件格式(unix=LF,dos=CRLF,mac=CR)
set fileformat=unix
set fileformats=unix,dos,mac

" 提示信息语言
set langmenu=en_US.utf-8
language messages en_US.utf-8

" 开启文件类型检测
filetype on

" 开启语法高亮
syntax on

" 显示行号
set number

" 设置缩进大小
set tabstop=4
set softtabstop=4
set shiftwidth=4

" 将制表符用空格代替
set expandtab

" 关闭兼容模式(使用VIM的键盘模式)
set nocompatible

" 历史记录数量
set history=1000

" 设置关键字符(遇到以下字符连接的单词时不进行换行)
set iskeyword+=_,$,@,%,#,-

" 设置退格键模式
set backspace=indent,eol,start

" 设置列提示(右下角)
set ruler

" 设置状态提示(左下角)
set showmode

" 启动的时候不显示提示信息
set shortmess=atI

" 关闭错误信息响铃
set noerrorbells

" 设置(括号)匹配模式
set showmatch

" 搜索时实时匹配关键字
set incsearch

" 搜索时高亮关键字
set hlsearch

" 设置自动缩进
set autoindent

" 设置结构缩进(换行时缩进与当前行相同)
set smartindent

" 关闭自动备份
set nobackup

" 设置当前行/列高亮
set cursorline
" set cursorcolumn

" 设置背景色主题
set background=dark

" 主题颜色
colorscheme desert 

" 状态行显示内容
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}:%{&fenc!=''?&fenc:&enc}]\ [TYPE=%Y]\ %r%h%=[POS=%l,%v][%p%%]\ [%{strftime(\"%Y/%m/%d\ %H:%M\")}]

" 状态行显示模式(0=不显示,1=两个窗口以上显示,2=始终显示)
set laststatus=2

" 设置字体
set guifont=Terminus:h10:cANSI

" 设置窗口大小
" set lines=35 columns=128

" GUI 隐藏菜单栏
" set guioptions-=m

" GUI 隐藏工具栏
set guioptions-=T
