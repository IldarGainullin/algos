set shiftwidth=4
set tabstop=4
set cin
set ai
set smarttab
set smartindent
set expandtab
autocmd filetype cpp nnoremap <F4> :!g++ % -ggdb -std=c++11 -o %:r <CR>
autocmd filetype cpp nnoremap<F5> :!g++ % -ggdb -std=c++11 -o %:r && ./%:r <CR>
au BufNewFile *.cpp 0r ~/.vim/sf/std.cpp
nmap <c-s> :w<CR>
imap <c-s> <Esc>:w<CR>a
map <C-l> :tabr<cr>

map <C-h> :tabl<cr>

map <C-t> :tabn<cr>
