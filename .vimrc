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
map <C-l> :tabnext<cr>
map <C-h> :tabprev<cr>
map <C-t> :tabnew <cr>
map <C-w> :q! <cr>


