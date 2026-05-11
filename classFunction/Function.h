#pragma once

class Function{
public:
    virtual ~Function() = default;
    virtual double calc(double x) const = 0;

    // Ошибки обрабатываются без исключений:
    // - возвращаем false при некорректных аргументах
    // - результат пишем в outResult
    bool integrate(double a, double b, int n, double& outResult) const;
    bool derivative(double x, double h, double& outResult) const;
};
