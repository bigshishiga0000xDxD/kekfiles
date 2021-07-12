set encoding=UTF-8

call plug#begin('/home/danil/.config/nvim/plugged')

Plug 'morhetz/gruvbox'
Plug 'itchyny/lightline.vim'

Plug 'preservim/nerdtree'
Plug 'christoomey/vim-tmux-navigator'

Plug 'Valloric/YouCompleteMe'
Plug 'chrisbra/Colorizer'
Plug 'https://gitlab.com/code-stats/code-stats-vim.git'

Plug 'sheerun/vim-polyglot'

Plug 'ryanoasis/vim-devicons'

call plug#end()


syntax enable
colorscheme gruvbox
set background=dark

let g:lightline = {
\ 'colorscheme': 'gruvbox',
\ 'separator': { 'left': '', 'right': '' },
\ 'subseparator': { 'left': '', 'right': '' }
\ }


let g:codestats_api_key=''
let g:ycm_global_ycm_extra_conf='~/.config/nvim/.ycm_extra_conf.py'

filetype plugin indent on

set tabstop=4
set shiftwidth=4
set expandtab
set autoread
set undofile
set cursorline
set ignorecase smartcase
set noshowmode
set number
set splitbelow
set splitright
set guicursor=

" remove preview window for ycm
set completeopt-=preview

" fix c++ lambdas indent
set cindent
set cinoptions+=j1,(0,ws,Ws


autocmd BufNewFile,BufRead config set filetype=dosini


inoremap {<CR> {<CR>}<ESC>O
inoremap {;<CR> {<CR>};<ESC>O

nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

nnoremap <C-N> :NERDTreeToggle<CR>

" don't move back when entering normal mode
imap <C-[> <Esc>`^


" use :call Start() to prepare workspace
" use <F5> to run program
" use <F6> to clear

:function Start()
    nnoremap ye <C-W><C-H>
    :e ~/cp/main.cpp
    :45vsplit ~/cp/input.txt
    :split ~/cp/output.txt
    normal ye
    normal G
    normal zz
:endfunction

:function Run()
    :wa
    :! ./run.sh
:endfunction

:function Clear()
    :! cat example.cpp > main.cpp && echo "" > input.txt && echo "" > output.txt
    :46
    normal zz
:endfunction


map <F5> :call Run() <CR>
map <F6> :call Clear() <CR>
