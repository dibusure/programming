let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
doautoall SessionLoadPre
silent only
silent tabonly
cd ~/Programming/code/KEGE/Openfipi/hw6
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess+=aoO
badd +1 ~/Programming/code/KEGE/Openfipi/hw6
badd +26 31519.py
badd +21 conspect.py
badd +1 statements.org
badd +5 term://~/Programming/code/KEGE/Openfipi/hw6//501335:/usr/sbin/sh
badd +24 28944.py
badd +4 27778.py
badd +0 greedy_algos
badd +5 greedy_1.py
badd +0 term://~/Programming/code/KEGE/Openfipi/hw6//541609:/bin/zsh
badd +0 greedy_1.cpp
argglobal
%argdel
$argadd ~/Programming/code/KEGE/Openfipi/hw6
edit greedy_1.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 30 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 98 + 86) / 172)
exe '2resize ' . ((&lines * 9 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 98 + 86) / 172)
exe 'vert 3resize ' . ((&columns * 73 + 86) / 172)
argglobal
balt greedy_1.py
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 15) / 30)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Programming/code/KEGE/Openfipi/hw6
wincmd w
argglobal
if bufexists(fnamemodify("term://~/Programming/code/KEGE/Openfipi/hw6//541609:/bin/zsh", ":p")) | buffer term://~/Programming/code/KEGE/Openfipi/hw6//541609:/bin/zsh | else | edit term://~/Programming/code/KEGE/Openfipi/hw6//541609:/bin/zsh | endif
if &buftype ==# 'terminal'
  silent file term://~/Programming/code/KEGE/Openfipi/hw6//541609:/bin/zsh
endif
balt ~/Programming/code/KEGE/Openfipi/hw6/greedy_1.py
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 112 - ((8 * winheight(0) + 4) / 9)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 112
normal! 025|
lcd ~/Programming/code/KEGE/Openfipi/hw6
wincmd w
argglobal
if bufexists(fnamemodify("~/Programming/code/KEGE/Openfipi/hw6/greedy_algos", ":p")) | buffer ~/Programming/code/KEGE/Openfipi/hw6/greedy_algos | else | edit ~/Programming/code/KEGE/Openfipi/hw6/greedy_algos | endif
if &buftype ==# 'terminal'
  silent file ~/Programming/code/KEGE/Openfipi/hw6/greedy_algos
endif
balt ~/Programming/code/KEGE/Openfipi/hw6/statements.org
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 20 - ((19 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 20
normal! 0
lcd ~/Programming/code/KEGE/Openfipi/hw6
wincmd w
exe '1resize ' . ((&lines * 30 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 98 + 86) / 172)
exe '2resize ' . ((&lines * 9 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 98 + 86) / 172)
exe 'vert 3resize ' . ((&columns * 73 + 86) / 172)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
