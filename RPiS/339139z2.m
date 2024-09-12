function out=new_gamma(k) #rekurencyjna funkcja obliczająca gammę
  if(k==1) #definicja
    out=1;
  elseif(k==1/2) #zad 3 lista 5
    out=sqrt(pi);
  else
    out=(k-1)*new_gamma(k-1); #zad 3 lista 1
  endif
endfunction

function out=gestosc(x,k) #funkcja z treści
  l1=e^(-x/2);
  l2=x^((k/2)-1);
  m1=2^(k/2);
  m2=new_gamma(k/2);
  out=l1*l2;
  out/=(m1*m2);
endfunction

function out=trapezy(x,k,n) #całkowanie za pomocą złożonego wzór trapezów
  s=0;
  h=x/n;
  for i=0:h:x
    t=gestosc(i,k);
    s+=2*t;
  endfor
  s-=gestosc(0,k);
  s-=gestosc(x,k);
  w=x/(2*n);
  out=w*s;
endfunction

w1=trapezy(3.357,4,100000);
w2=trapezy(1.0216,2,1000);
w3=trapezy(1.005,3,1000);
#wyniki sprawdzone z kalkulatorem: https://homepage.divms.uiowa.edu/~mbognar/applets/chisq.html
