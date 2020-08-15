set encoding=UTF-8

call plug#begin('~/.vim/plugged')

Plug 'morhetz/gruvbox'
Plug 'https://gitlab.com/code-stats/code-stats-vim.git'
Plug 'sheerun/vim-polyglot'
Plug 'preservim/nerdtree'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'ryanoasis/vim-devicons'

call plug#end()

colorscheme gruvbox
set background=dark
set guifont=hack
let g:airline_theme='base16_gruvbox_dark_hard'

let g:codestats_api_key='SFMyNTY.WVdGNWVXcz0jI01UQTFORE09.zZHDjkyyNhks48imagMmSSw34CYYvVVisOE21mYybdY'

filetype plugin indent on
set tabstop=4
set shiftwidth=4
set expandtab
set autoread

inoremap {<CR> {<CR>}<ESC>O
inoremap {;<CR> {<CR>};<ESC>O

nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

nnoremap <C-B> :NERDTreeToggle<CR>
nnoremap ye <C-W><C-H>

:function Start()
    set splitbelow
    set splitright

    :e ~/cp/main.cpp
    :45vsplit ~/cp/input.txt
    :split ~/cp/output.txt
    normal ye
    normal G
    normal zz
:endfunction

map <C-x> :call Run() <CR>

:function Run()
    :wa
    :! bash -c "cd ~/cp && ./run.sh"
:endfunction
