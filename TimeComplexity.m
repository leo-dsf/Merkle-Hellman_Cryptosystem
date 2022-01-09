M = readmatrix("resultsALL");
M1 = readmatrix("resultsPartial");

timingsM0 = reshape(M(M(:, 1) == 0, 5), 20, []);
averageM0 = mean(timingsM0);
minM0 = min(timingsM0);
maxM0 = max(timingsM0);

timingsM1 = reshape(M(M(:, 1) == 1, 5), 20, []);
averageM1 = mean(timingsM1);
minM1 = min(timingsM1);
maxM1 = max(timingsM1);

timingsM2 = reshape(M(M(:, 1) == 2, 5), 20, []);
averageM2 = mean(timingsM2);
minM2 = min(timingsM2);
maxM2 = max(timingsM2);

timingsM3 = reshape(M(M(:, 1) == 3, 5), 20, []);
averageM3 = mean(timingsM3);
minM3 = min(timingsM3);
maxM3 = max(timingsM3);

timingsM4 = reshape(M1(M1(:, 1) == 2, 5), 20, []);
averageM4 = mean(timingsM4);
minM4 = min(timingsM4);
maxM4 = max(timingsM4);

figure(1);
semilogy((1:length(averageM0)) + 9, averageM0, ".-", 'DisplayName', "BF - Média"); hold on;
semilogy((1:length(minM0)) + 9, minM0, ".-", 'DisplayName', "BF - Mínimo"); hold on;
semilogy((1:length(maxM0)) + 9, maxM0, ".-", 'DisplayName', "BF - Máximo"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;

figure(2);
semilogy((1:length(averageM1)) + 9, averageM1, ".-", 'DisplayName', "CBF - Média"); hold on;
semilogy((1:length(minM1)) + 9, minM1, ".-", 'DisplayName', "CBF - Mínimo"); hold on;
semilogy((1:length(maxM1)) + 9, maxM1, ".-", 'DisplayName', "CBF - Máximo"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;

figure(3);
semilogy((1:length(averageM2)) + 9, averageM2, ".-", 'DisplayName', "HS - Média"); hold on;
semilogy((1:length(minM2)) + 9, minM2, ".-", 'DisplayName', "HS - Mínimo"); hold on;
semilogy((1:length(maxM2)) + 9, maxM2, ".-", 'DisplayName', "HS - Máximo"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;

figure(4);
semilogy((1:length(averageM3)) + 9, averageM3, ".-", 'DisplayName', "SS - Média"); hold on;
semilogy((1:length(minM3)) + 9, minM3, ".-", 'DisplayName', "SS - Mínimo"); hold on;
semilogy((1:length(maxM3)) + 9, maxM3, ".-", 'DisplayName', "SS - Máximo"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;

figure(5);
semilogy((1:length(averageM4)) + 9, averageM4, ".-", 'DisplayName', "RNO - Média"); hold on;
semilogy((1:length(minM4)) + 9, minM4, ".-", 'DisplayName', "RNO - Mínimo"); hold on;
semilogy((1:length(maxM4)) + 9, maxM4, ".-", 'DisplayName', "RNO - Máximo"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;

figure(6);
semilogy((1:length(averageM0)) + 9, averageM0, ".-", 'DisplayName', "BF - Média"); hold on;
semilogy((1:length(averageM1)) + 9, averageM1, ".-", 'DisplayName', "CBF - Média"); hold on;
semilogy((1:length(averageM2)) + 9, averageM2, ".-", 'DisplayName', "HS - Média"); hold on;
semilogy((1:length(averageM3)) + 9, averageM3, ".-", 'DisplayName', "SS - Média"); hold on;
semilogy((1:length(averageM4)) + 9, averageM4, ".-", 'DisplayName', "RNO - Média"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;

figure(7);
semilogy((1:length(averageM0)) + 9, averageM0, ".-", 'DisplayName', "BF - Média"); hold on;
semilogy((1:length(minM0)) + 9, minM0, ".-", 'DisplayName', "BF - Mínimo"); hold on;
semilogy((1:length(maxM0)) + 9, maxM0, ".-", 'DisplayName', "BF - Máximo"); hold on;

semilogy((1:length(averageM4)) + 9, averageM4, ".-", 'DisplayName', "RNO - Média"); hold on;
semilogy((1:length(minM4)) + 9, minM4, ".-", 'DisplayName', "RNO - Mínimo"); hold on;
semilogy((1:length(maxM4)) + 9, maxM4, ".-", 'DisplayName', "RNO - Máximo"); hold on;

semilogy((1:length(averageM1)) + 9, averageM1, ".-", 'DisplayName', "CBF - Média"); hold on;
semilogy((1:length(minM1)) + 9, minM1, ".-", 'DisplayName', "CBF - Mínimo"); hold on;
semilogy((1:length(maxM1)) + 9, maxM1, ".-", 'DisplayName', "CBF - Máximo"); hold on;

semilogy((1:length(averageM2)) + 9, averageM2, ".-", 'DisplayName', "HS - Média"); hold on;
semilogy((1:length(minM2)) + 9, minM2, ".-", 'DisplayName', "HS - Mínimo"); hold on;
semilogy((1:length(maxM2)) + 9, maxM2, ".-", 'DisplayName', "HS - Máximo"); hold on;

semilogy((1:length(averageM3)) + 9, averageM3, ".-", 'DisplayName', "SS - Média"); hold on;
semilogy((1:length(minM3)) + 9, minM3, ".-", 'DisplayName', "SS - Mínimo"); hold on;
semilogy((1:length(maxM3)) + 9, maxM3, ".-", 'DisplayName', "SS - Máximo"); hold on;
xlabel("Valores de N");
ylabel("Tempo(segundos)");
grid on;
legend;