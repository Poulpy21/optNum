

//exec('test.sce')


function [f,g] = f1(x)
	
	poids = [1:size(x,1)]
	f = x' * ((poids').*x)
	
	//Le gradient
	g = 2*x.*poids'

endfunction

function [f,g] = f2(x)
	f = (1-x(1)^2) + 100*(x(2)-x(1)^2)^2

	g = [-2*(1-x(1))-2*x(1)*100*2*(x(2)-x(1)^2) , 2*100*(x(2) - x(1)^2) ]'

endfunction


function [x] = optimiseur(x0, simulateur, t, n)
	
	x = zeros(2,n+1)
	x(:,1) = x0

	for i=1:n,
		[f,g] = simulateur(x(:,i))
		d = -g
		
		x(:,i+1) = x(:,i) + t*d

		//Critère de fin
	end
endfunction

function [x] = optimiseurWolfe(x0, simulateur, epsilon)
        
        x = x0

        while(%T)
		[f,g] = simulateur(x)
		d = -g
	        
                t = Wolfe(x, d, simulateur)
		x = x + t*d

		//Critère de fin
                if abs(d) < epsilon
                        break
                end
	end
endfunction

function [t] = Wolfe(x_k, d_k, simulateur)

        t = 1

        tg = 0
        td = %inf

        m1 = 0.1
        m2 = 0.9

        [f0, df0] = simulateur(x_k)
        q0 = f0
        dq0 = df0'*d_k
        
        i = 0
        while(%T),
                x_k_tild = x_k + t*d_k
                [f, df] = simulateur(x_k_tild)
               
                i = i + 1
                q = f
                dq = df'*d_k
                disp("Passage " + string(i) + " q = " + string(q)+ " dq = " + string(dq) + " t = " + string(t))
                sleep(500)
                
                if (q <= q0 + m1*t*dq0) & (dq >= m2*dq0) then
                        disp("break !")
                        break 
                elseif (q > q0 + m1*t*dq0) then
                        disp("trop grand !")
                        td = t
                elseif (q <= q0 + m1*t*dq0) & (dq < m2*dq0) then
                        disp("trop petit !")
                        tg = t
                end

                if (td == %inf) then
                        t = 10*tg
                else
                        t = (tg+td)/2
                end
        end

        disp("sortie")

endfunction


function [x] = BFGS(simulateur, x0, epsilon)
        
        xk = x0
        [fk, gk] = simulateur(x0)

        n = size(x0,1)
        Wk = eye(n,n)

        
        
        while %T
                dk = - Wk*gk
                tk = Wolfe(xk, dk, simulateur)

                xk1 = xk - tk * Wk * gk

                [fk1, gk1] = simulateur(xk1);
                
                Wk =  Wk1(xk, xk1, gk, gk1, Wk)
                
                if abs(xk - xk1) < epsilon
                        break
                end

                gk = gk1
                xk = xk1
        end
        
        x = xk1

endfunction

function W = Wk1(xk, xk1, dfxk, dfxk1, Wk) 
        
        sk = xk1 - xk
        yk = dfxk1 - dfxk
        
        //disp(yk'*sk)
        W = Wk - (sk*yk'*Wk + Wk*yk*sk')/(yk'*sk) + [1 + (yk'*Wk*yk)/(yk'*sk)] * (sk*sk')/(yk'*sk)

endfunction

        
