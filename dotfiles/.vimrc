set encoding=UTF-8

call plug#begin('~/.vim/plugged')

Plug 'jacoborus/tender.vim'
Plug 'itchyny/lightline.vim'

Plug 'https://gitlab.com/code-stats/code-stats-vim.git'
Plug 'sheerun/vim-polyglot'
Plug 'preservim/nerdtree'
Plug 'Valloric/YouCompleteMe'
Plug 'christoomey/vim-tmux-navigator'
Plug 'ryanoasis/vim-devicons'

call plug#end()

set clipboard+=unnamedplus

set guicursor=

" If you have vim >=8.0 or Neovim >= 0.1.5
if (has("termguicolors"))
 set termguicolors
endif

" For Neovim 0.1.3 and 0.1.4
let $NVIM_TUI_ENABLE_TRUE_COLOR=1

" Theme
syntax enable
colorscheme tender

" set lighline theme inside lightline config
let g:lightline = {
\ 'colorscheme': 'tender',
\ 'separator': { 'left': '', 'right': '' },
\ 'subseparator': { 'left': '', 'right': '' }
\ }
set noshowmode

set completeopt-=preview

let g:codestats_api_key='SFMyNTY.WVdGNWVXcz0jI01UQTFORE09.ISH3rOH-xWLU_ZZ3LYSCpukg7JsilVHgBp6HSFFjc8o'

filetype plugin indent on
set tabstop=4
set shiftwidth=4
set expandtab
set autoread
setlocal cindent
setlocal cinoptions=h1,l1,g1,t0,i4,j1,+4,(0,ws,wS,w1,W4

inoremap {<CR> {<CR>}<ESC>O
inoremap {;<CR> {<CR>};<ESC>O

nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

imap <C-[> <Esc>`^

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
    :! ./run.sh
:endfunction

map <C-c> :call Clear() <CR>

:function Clear()
    :! cat example.cpp > main.cpp && echo "" > input.txt && echo "" > output.txt
    :46
    normal zz
:endfunction
