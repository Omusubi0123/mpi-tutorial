#!/bin/bash
prefix=mpi-tutorial
src=${prefix}.typ
dst=${prefix}.pdf
typst watch --open evince ${src} ${dst} &
