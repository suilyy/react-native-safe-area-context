//@ts-check
const fs = require('fs');
const path = require('path');
const readline = require('readline');
const { execSync } = require('node:child_process');
const JSON5 = require('json5');

const PACKAGE_DIR_NAME = 'react-native-safe-area-context';
const MODULE_NAME = 'safe_area';
const PACKAGE_TGZ_STEM_NAME_WITHOUT_VERSION =
  'rnoh-react-native-safe-area-context';

(async function main() {
  const newVersionIndex = process.argv.findIndex(
    (arg) => arg === '--new-version'
  );
  // const testerPathIndex = process.argv.findIndex(
  //   (arg) => arg === '--tester-path'
  // );
  let version,testerPath;

  if (newVersionIndex !== -1 && process.argv[newVersionIndex + 1]) {
    version = process.argv[newVersionIndex + 1];
  } else {
    const currentVersion = readPackage('.').version;
    version = await askUserForVersion(currentVersion);
  }
  
  // if (testerPathIndex !== -1 && process.argv[testerPathIndex + 1]) {
  //   testerPath = process.argv[testerPathIndex + 1];
  // } else {
  //   console.log('Deployment aborted');
  //   process.exit(1);
  // }


  updatePackageVersion('.', version);
  console.log(`Updated ${PACKAGE_DIR_NAME}/package.json`);
  // updatePackageScript(testerPath, version);
  // console.log('Updated tester/package.json');
  console.log(
    `${process.cwd()}/harmony/${MODULE_NAME}/oh-package.json5`);
  updateOHPackageVersion(
    `${process.cwd()}/harmony/${MODULE_NAME}/oh-package.json5`,
    version
  );
  // updateOHPackageVersion(
  //   `${testerPath}/harmony/${MODULE_NAME}/oh-package.json5`,
  //   version
  // );
  // console.log(`Updated ${MODULE_NAME}/oh-package.json5`);
  // execSync(`npm i && cd ${testerPath}`, { stdio: 'inherit' });
})();

/**
 * @param {string} currentVersion
 * @returns {Promise<string>}
 */
function askUserForVersion(currentVersion) {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  return new Promise((resolve) => {
    rl.question(
      `Current version: ${currentVersion}. Enter new version: `,
      (userInput) => {
        rl.close();
        resolve(userInput);
      }
    );
  });
}

/**
 * @param {string} packageDir
 * @returns {{version: string, scripts?: Record<string, string>}} - parsed content of package.json
 */
function readPackage(packageDir) {
  const packageJsonPath = path.join(packageDir, 'package.json');
  const packageContent = fs.readFileSync(packageJsonPath, 'utf-8');
  return JSON.parse(packageContent);
}

/**
 * @param {string} packageDir
 * @param {string} version
 */
function updatePackageVersion(packageDir, version) {
  const packageData = readPackage(packageDir);
  packageData.version = version;

  const packageJsonPath = path.join(packageDir, 'package.json');
  fs.writeFileSync(
    packageJsonPath,
    JSON.stringify(packageData, null, 2),
    'utf-8'
  );
}

/**
 * @param {string} packageDir
 * @param {string} version
 */
function updatePackageScript(packageDir, version) {
  const packageData = readPackage(packageDir);

  for (let script in packageData.scripts) {
    const regex = new RegExp(
      `${PACKAGE_TGZ_STEM_NAME_WITHOUT_VERSION}-\\d*\\.\\d*\\.\\d*`,
      'g'
    );
    packageData.scripts[script] = packageData.scripts[script].replace(
      regex,
      `${PACKAGE_TGZ_STEM_NAME_WITHOUT_VERSION}-${version}`
    );
  }
  const packageJsonPath = path.join(packageDir, 'package.json');
  fs.writeFileSync(
    packageJsonPath,
    JSON.stringify(packageData, null, 2),
    'utf-8'
  );
}
/**
 * @param {string} ohPackagePath
 * @param {string} version
 */
function updateOHPackageVersion(ohPackagePath, version) {
  console.log('ohPackageContent',process.cwd() + ohPackagePath, fs.existsSync(process.cwd() + ohPackagePath))
  const ohPackageContent = JSON5.parse(
    
    fs.readFileSync(ohPackagePath, 'utf8').toString()
  );
  ohPackageContent.version = version;
  fs.writeFileSync(ohPackagePath, JSON5.stringify(ohPackageContent, null, 2));
}