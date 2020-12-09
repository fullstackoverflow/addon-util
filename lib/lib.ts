import { promisify } from "util";
import { readFileSync } from "fs";
import { resolve } from "path";

const _Util = require("bindings")("Util").Util;

export class Util extends _Util {

    async AsyncWorker(input_1: number, input_2: number): Promise<{ result: number, tag: boolean }> {
        const { result, tag } = await super.AsyncWorker(input_1, input_2);
        return { result, tag };
    }
}