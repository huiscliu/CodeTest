c subroutine: y = ax + y
      subroutine ftn_axpy (a, x, y, n)

      implicit none

      integer n, i
      double precision a
      double precision, dimension(0:n-1):: x
      double precision, dimension(0:n-1):: y

      do i = 0, n-1
          y(i) = a * x(i) + y(i)
      enddo

      return
      end 

c subroutine: y = aAx + y
      subroutine ftn_amxpy(a, Ap, Aj, Ax, x, y, n)
      implicit none

      integer n
      integer i, j, nrow, nend
      double precision a, t
      double precision, dimension(0:n-1) :: x
      double precision, dimension(0:n-1) :: y

      integer, dimension(0:n) :: Ap
      integer, dimension(0:Ap(n)-1) :: Aj
      double precision, dimension(0:Ap(n)-1):: Ax

      nrow = n - 1

!$omp parallel 
!$omp do
      do i = 0, nrow
          nend = Ap(i + 1)

          t = 0
          do j = Ap(i), nend
              t = t + Ax(j) * x(Aj(j))
          enddo

          y(i) = a * t + y(i)
      enddo
!$omp end do
!$omp end parallel

      return
      end
