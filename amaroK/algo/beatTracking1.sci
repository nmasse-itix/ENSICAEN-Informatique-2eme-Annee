function outSamples = beatTracking1(fileName)

// Read samples
[samples sampleFreq nBits] = wavread(fileName);

// We keep only the first channel
samples = samples(1, :);
outSamples = samples;

// Computes size
[nChannels nSamples] = size(samples);

// Instant energy
instantEnergyWindow = 1024;
instantEnergies = nSamples / instantEnergyWindow;

// Average energy
averageEnergyWindow = 43;
averageEnergies = instantEnergies;

beatConstant = 1.3;
beatRatio = .01;

// Time arrays
t = [0 : nSamples - 1];
tEnergies = [0 : instantEnergies - 1] * instantEnergyWindow;

// Energies arrays
instantEnergy = zeros(1, instantEnergies);
averageEnergy = zeros(1, averageEnergies);


// Compute instant energy
for i = [0 : instantEnergies - 1],
	tsum = 0;
	for s = [(i * instantEnergyWindow) + 1: ((i + 1) * instantEnergyWindow)],
		tsum = tsum + samples(s)^2;
	end
	instantEnergy(i + 1) = tsum;
end

// running windowed sum of instant energies
tmpEnergy = 0;
for i = [1 : averageEnergyWindow],
	tmpEnergy = tmpEnergy + instantEnergy(i);
end
averageEnergy(1) = tmpEnergy;

for i = [2 : averageEnergies - averageEnergyWindow],
	averageEnergy(i) = averageEnergy(i - 1) - instantEnergy(i - 1) + instantEnergy(i + averageEnergyWindow - 1);
end

for i = [averageEnergies - averageEnergyWindow + 1: averageEnergies],
	averageEnergy(i) = averageEnergy(i - 1) - instantEnergy(i - 1);
end

// average the sum
averageEnergy = averageEnergy / averageEnergyWindow;

// computes the variance
energyVariance = zeros(averageEnergy);
for i = [1 : averageEnergies],
	v = 0
	for j = [i : i + averageEnergyWindow - 1],
		if j <= instantEnergies then
			v = v + (instantEnergy(j) - averageEnergy(i))^2;
		end
	end
	energyVariance(i) = v;
end
energyVariance = sqrt(energyVariance);

// Computes the beat detection constants
beatConstants = -0.0025714 * energyVariance + 1.5142857;

// Compares the instant energies and the average energies
difference = instantEnergy - beatConstant * averageEnergy;
difference2 = instantEnergy - beatConstants .* averageEnergy;

// averages the difference
h = [.2 .2 .2 .2 .2];
filteredDifference = convol(h, difference);
filteredDifference = filteredDifference(3 : averageEnergies + 2);

filteredDifference2 = convol(h, difference2);
filteredDifference2 = filteredDifference2(3 : averageEnergies + 2);

// Ratio computation
ratio = zeros(instantEnergy);
for i = [1 : instantEnergies],
	if averageEnergy(i) <> 0  then
		ratio(i) = instantEnergy(i) / averageEnergy(i);
	end
end

// Beat detection
beatIdx = 1;
beat = [];
for i = [1 : instantEnergies - 1],
	//if (ratio(i) < beatRatio) & (ratio(i+1) > beatRatio) then
	//if (filteredDifference(i) < 0) & (filteredDifference(i+1) > 0) then
	if (filteredDifference(i) < 0) & (filteredDifference(i+1) > 0) then
	//if (difference(i) < 0) & (difference(i+1) > 0) then
		// draws a line
		beat(beatIdx) = tEnergies(i);
		beatIdx = beatIdx + 1;
	end
end

beatIdx2 = 1;
beat2 = [];
for i = [1 : instantEnergies - 1],
	//if (ratio(i) < beatRatio) & (ratio(i+1) > beatRatio) then
	if (filteredDifference2(i) < 0) & (filteredDifference2(i+1) > 0) then
	//if (difference(i) < 0) & (difference(i+1) > 0) then
		// draws a line
		beat2(beatIdx2) = tEnergies(i);
		beatIdx2 = beatIdx2 + 1;

		// put a beep (4000 Hz) in the signal
		for j = [0 : sampleFreq / 100],
			outSamples(tEnergies(i) + j) = .9 * sin(2 * %pi * (j * sampleFreq / 4000));
		end
	end
end

// Plotting...
scf(1);
subplot(2, 1, 1);
plot2d(t, samples, style=color('grey'));
for i = [1 : beatIdx - 1],
	xsegs([beat(i) beat(i)], [.2 -.2], color('red'));
end
xtitle('Echantillons de ' + fileName , 'echantillons', 'amplitude');

subplot(2, 1, 2);
plot2d(tEnergies, instantEnergy, style=color('green'));
plot2d(tEnergies, averageEnergy, style=color('blue'));
xtitle('Energies de ' + fileName, 'echantillons', 'energie');
legend(['Energie instantanee', 'Energie moyenne'], 1, %t);

scf(2);
subplot(3, 1, 1);
plot2d(tEnergies, instantEnergy, style=color('green'));
plot2d(tEnergies, averageEnergy, style=color('blue'));
xtitle('Energies of ' + fileName, 'samples', 'energy');
legend(['Instant energy', 'Average energy'], 1, %t);

subplot(3, 1, 2);
plot2d(tEnergies, energyVariance, style=color('purple'));
xtitle('Energy variance of ' + fileName, 'samples', 'variance');

subplot(3, 1, 3);
plot2d(tEnergies, beatConstants, style=color('red'));
xtitle('Evolution of the beat detection constant of ' + fileName, 'samples');

scf(3);
subplot(2, 1, 1);
plot2d(tEnergies, difference, style=color('cyan'));
plot2d(tEnergies, filteredDifference, style=color('red'));
plot2d([tEnergies(1) tEnergies(instantEnergies)], [0 0]);
xtitle('Difference between instant and ' + string(beatConstant) + ' * average energies of ' + fileName, 'samples');
legend(['Difference', 'Average difference'], 1, %t);

subplot(2, 1, 2);
plot2d(tEnergies, difference2, style=color('cyan'));
plot2d(tEnergies, filteredDifference2, style=color('red'));
plot2d([tEnergies(1) tEnergies(instantEnergies)], [0 0]);
xtitle('Difference between instant and computed constant * average energies of ' + fileName, 'samples');


scf(4);
plot2d(tEnergies, ratio, style=color('orange'), logflag='nl');
plot2d([tEnergies(1) tEnergies(instantEnergies)], [beatRatio beatRatio]);
xtitle('Ratio between instant and average energies of ' + fileName, 'samples');
legend(['Ratio', 'Beat detection limit'], 4, %t);

scf(5);
subplot(3, 1, 1);
plot2d(t, samples, style=color('grey'));
for i = [1 : beatIdx - 1],
	xsegs([beat(i) beat(i)], [.2 0], color('blue'));
end
for i = [1 : beatIdx2 - 1],
	xsegs([beat2(i) beat2(i)], [-.2 0], color('red'));
end
xtitle('Echantillons de ' + fileName , '', 'amplitude');

subplot(3, 1, 2);
plot2d(tEnergies, filteredDifference, style=color('blue'));
plot2d([tEnergies(1) tEnergies(instantEnergies)], [0 0]);
xtitle('Difference lissee entre l`energie instantanee et ' + string(beatConstant) + ' * l`energie moyenne de ' + fileName);

subplot(3, 1, 3);
plot2d(tEnergies, filteredDifference2, style=color('red'));
plot2d([tEnergies(1) tEnergies(instantEnergies)], [0 0]);
xtitle('Difference lissee entre l`energie instantanee et C(i) * l`energie moyenne de ' + fileName);

