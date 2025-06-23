#import "@preview/touying:0.6.1": *
// #import themes.metropolis: *
#import themes.university: *
// #import themes.aqua: *
// #import themes.dewdrop: *
// #import themes.simple: *
// #import themes.stargazer: *
// #import themes.default: *

#import "@preview/numbly:0.1.0": numbly

#show: university-theme.with(
  aspect-ratio: "16-9",
  align: horizon,
  config-common(handout: true),
  config-info(
    title: [MPI],
    subtitle: [Spring Training 2025],
    author: [Yoshihiro Izawa],
    date: [2025/05/13],
  ),
  config-colors(
    primary: rgb("#8e690c"),
    primary-light: rgb("#0d8590"),
    primary-lightest: rgb("#e0ecf2"),
    neutral-lightest: rgb("#ffffff")
  ),
)
#set text(font: "Noto Serif CJK JP", size: 18pt)
#set quote(block: true)
#let ao(x) = text(blue, x)
#let small(x) = text(size: 16pt)[#x]
#let blink(x, y) = text(blue, link(x, y))

/* include image sequence xxx_L1.svg, xxx_L2.svg, ... */
#let images(prefix, rng, ..kwargs) = for (i, j) in rng.enumerate() [
  #only(i+1, image(prefix + "_L" + str(j) + ".svg", ..kwargs))
]

#show raw.where(block: true): it => {
  set text(size: 12pt) // フォントサイズ
  box(
    fill: rgb("#f5f5f5"), // ごく薄いグレーの背景色
    inset: (left: 1em, right: 1em, top: 0.5em, bottom: 0.5em), // 内側の余白を調整
    width: 100%, // 幅を親要素に合わせる
    radius: 4pt, // 角を少し丸める（任意）
    it
  )
}
#show raw.where(block: false): it => text(rgb(127,127,127), size: 16pt, it)

#set heading(numbering: numbly("{1}.", default: "1.1"))

#show label("blue"): set text(blue)
#show label("red"): set text(red)

#title-slide()
#outline(depth: 1)

= MPI Overview

== What is MPI (Message Passing Interface)?

- *A standard API* for message passing between distributed memories in parallel computing.
- MPI assumes a *distributed-memory computing system*
- MPI can run on *shared-memory computing system*
- MPI programming model (basically) uses *SIMD*

== Parallel Programming Classification

- *Multi-Process*: 
    MPI(Message Passing Interface), HPF(High Performance Fortran)
- *Multi-Thread*: OpenMP, Pthread(POSIX Thread)

== MPI Features

- *Communication Model*: Uses message passing for communication between processes.
- *Distributed Memory Support*: Each process has its own memory space, no shared memory.
- *Multi-node Capacity*: Can run across multiple nodes; abstracts network communication.
- *Standardized API*: Standardized interface in C, C++, and Fortran; hightly portable.
- *Multiple Implementation*: Available implementations include OpenMPI, MPICH, and Intel MPI, etc.
- *Difficalt to Debug*: Debugging is challenging due to concurrency and communiaction complexity.

== Typical example of Usage
- Simulation on a supercomputer(Physics, Meteorology, Chemistry, etc.)
- Data processing in large-scale data analysis (e.g., genomics, astronomy).
- Machine learning training on large datasets (e.g., distributed deep learning).

== Comparison between implementations

#slide[
  #set text(size: 16pt)
  #table(
    columns: (auto, auto, auto, auto),
    inset: 7pt,
    align: center + horizon,
    stroke: 0.5pt,
    [], [*OpenMPI*], [*MPICH*], [*Intel MPI*],
    [*Developer*], [Universities, Companies], [Argonne National Laboratory], [Intel Corporation],
    [*Distribution*], [Open source], [Open source], [Free version included],
    [*Optimization Target*], [General purpose], [Lightweight, stable], [Optimized for Intel architecture],
    [*Performance*], [Medium to high], [Lightweight, stable, scalable], [Best performance on Intel CPUs],
    [*Main Use*], [Academic clusters, general HPC], [Research, education], [Commercial HPC, Intel clusters],
  )
  #set text(size: 16pt)
]


== Key Communication Primitives

- *System function*: `MPI_Init`, `MPI_Finalize`, `MPI_Comm_size`, `MPI_Comm_rank`
- *Point-to-point communication*: `MPI_Send`, `MPI_Recv`
- *Collective communication*: `MPI_Bcast`, `MPI_Reduce`, `MPI_Alltoall`
- *Synchronization*: `MPI_Barrier`, `MPI_Wait`, `MPI_Test`
- *Derived data types*: `MPI_Type_create_struct`, `MPI_Type_vector`
- *Non-blocking communication*: `MPI_Isend`, `MPI_Irecv`
- *Remote memory access*: `MPI_Put`, `MPI_Get`
- *Process management*: `MPI_Comm_spawn`, `MPI_Comm_free`


== Minimum MPI Program

#slide(composer: (3fr, 2fr))[
=== Hello World (C)
```c
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int num_procs;
    int my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("Num of Proc : %d\n", num_procs);
    printf("My Rank     : %d\n", my_rank);

    MPI_Finalize();
    return EXIT_SUCCESS;
}
```
][
```sh
mpicc mpi_hello.c -o mpi_hello
mpirun -np 4 ./mpi_hello
Num of Proc : 4
My Rank     : 3
Num of Proc : 4
My Rank     : 2
Num of Proc : 4
My Rank     : 0
Num of Proc : 4
My Rank     : 1
```
]

#slide(composer: (3fr, 2fr))[
=== Hello World (C++)
```cpp
#include <mpi.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int num_procs;
    int my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    std::cout << "Num of Proc : " << num_procs << std::endl;
    std::cout << "My Rank     : " << my_rank << std::endl;

    MPI_Finalize();
    return EXIT_SUCCESS;
}
```
][
```sh
mpic++ mpi_hello.cpp -o mpi_hello
mpirun -np 4 ./mpi_hello
Num of Proc : 4
My Rank     : 3
Num of Proc : 4
My Rank     : 1
Num of Proc : 4
My Rank     : 0
Num of Proc : 4
My Rank     : 2
```
]

#slide(composer: (3fr, 2fr))[
=== Hello World (Fortran)
```fortran
program hello_mpi
  use mpi
  implicit none

  integer :: ierr, rank, size

  call MPI_Init(ierr)
  call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
  call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)

  print *, "Num of Proc:", size
  print *, "My Rank:    ", rank

  call MPI_Finalize(ierr)
end program hello_mpi
```
][
```sh
mpif90 mpi_hello.f90 -o mpi_hello
mpirun -np 4 ./mpi_hello
Num of Proc:            4
My Rank:                2
Num of Proc:            4
My Rank:                0
Num of Proc:            4
My Rank:                3
Num of Proc:            4
My Rank:                1
```
]

== Communicator
- *MPI_COMM_WORLD*: Default communicator for all processes in MPI. Determines the processer group.
- At 

= Basic Learning of MPI

= References

== MPI Reference
- #blink("https://www.cc.u-tokyo.ac.jp/events/lectures/17/MPIprogC.pdf")[MPI「超」入門（C言語編）- 東京大学情報基盤センター]
- #blink("https://www.hpci-office.jp/documents/HPC_Programming_Seminar/MPI_20240529.pdf")[並列プログラミング入門]


// #slide(composer: (2fr, 1fr))[

// ][

// ]
