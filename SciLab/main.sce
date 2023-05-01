function ans=f(x)
    x1 = x(1)
    x2 = x(2)
    ans = [x1 ^ 3 - x2 ^ 2 - 1; x1 * x2 ^ 3 - x2 - 4]
endfunction

function ans=jacobi_1(x)
    x1 = x(1)
    x2 = x(2)
    ans = [3 * x2 ^ 2 * x1 - 1, 2 * x2; -x2 ^ 3, 3 * x1 ^ 2]
    ans = ans ./ (9 * x1 ^ 3 * x2 ^ 2 - 3 * x1 ^ 2 + 2 * x2 ^ 4)
endfunction

function ans=is_end(x_prev, x, fx, err1, err2)
    delta1 = max(abs(fx))
    delta2 = 0
    for i=1:length(x)
        elem = x(i)
        if abs(elem) < 1 then
            val = abs(elem - x_prev(i))
        else
            val = abs(1 - x_prev(i) / elem)
        end
        if val > delta2 then
            delta2 = val
        end
    end
    mprintf("delta1 = %.17g delta2 = %.17g\n", delta1, delta2)
    if delta1 > err1 then
        ans = %F
        return
    end
    if delta2 > err2 then
        ans = %F
        return
    end
    ans = %T
endfunction

function str=array_to_string(x)
    str = "["
    for i=1:length(x)
        format(19)
        str = str +string(x(i))
        if i ~= length(x) then
            str = str + ", "
        end
    end
    str = str + "]"
endfunction

x = [1.2; 1.3]
mprintf("0: " + array_to_string(x') + "\n")
i = 1
fx = f(x)
x_next = x - jacobi_1(x) * fx
mprintf("1: " + array_to_string(x_next') + " ")
while ~is_end(x, x_next, fx, 1e-9, 1e-9) & i <= 1000
    x = x_next
    fx = f(x)
    x_next = x - jacobi_1(x) * fx
    i = i + 1
    mprintf(string(i) + ": " + array_to_string(x_next') + " ")
end
mprintf("Ответ: " + array_to_string(x_next') + "\n")
